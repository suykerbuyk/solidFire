/* vim: tabstop=4:softtabstop=4:shiftwidth=4:noexpandtab
 * =====================================================================================
 *
 *       Filename:  FileFinder.cpp
 *
 *    Description:  Implemntation of FileFinder
 *                  A multi-threaded class to find all files in a directory path.
 *
 *        Version:  1.0
 *        Created:  09/14/2013 13:22:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Suykerbuyk
 *   Organization:  SolidFire
 *
 * =====================================================================================
 */

#include <iostream>
#include <boost/thread.hpp>
#include "FileFinder.hpp"
#include "ThreadCounter.hpp"

namespace jos
{
	FileFinder::FileFinder()
	{
		p_thread_counter = new ThreadCounter;
	}
	FileFinder::~FileFinder()
	{
		delete p_thread_counter;
	}
	
	void FileFinder::Find(fs::path aDir, file_path_list_t& cwd_paths, std::string file_extension)
	{
		m_ext = file_extension;
		findFiles(aDir, cwd_paths, false);
	}
	void FileFinder::findFiles(fs::path aDir, file_path_list_t& cwd_paths, bool as_thread)
	{
		typedef std::list<file_path_list_t> child_paths_t;
		typedef std::list<file_path_list_t>::iterator child_paths_iterator_t;

		child_paths_t child_paths;
		if ( fs::exists(aDir) && fs::is_directory(aDir))
		{
			boost::thread_group threads;
			fs::directory_iterator end_iter;
			for( fs::directory_iterator dir_iter(aDir) ;  dir_iter != end_iter ;  ++dir_iter)
			{
				if (fs::is_regular_file(dir_iter->status()) )
				{
					if (fileExtMatch(dir_iter->path()))
					{
						cwd_paths.push_back(dir_iter->path());
					}
				} 
				else if (fs::is_directory(dir_iter->status()))
				{
					file_path_list_t child;
					child_paths.push_back(child);

					if (p_thread_counter->TryInc())
					{
						threads.create_thread( 
							boost::bind(&FileFinder::findFiles, 
							this, 
							dir_iter->path(), 
							boost::ref(child_paths.back()),true));
					}
					else
					{
						findFiles(dir_iter->path(), boost::ref(child_paths.back()), false);
					}
				}
				else
				{
					std::cerr << "Skipping: " << dir_iter->path() << std::endl;
				}
			}
			threads.join_all();
			//cwd_paths.sort();
			if (child_paths.size())
			{
				child_paths_iterator_t child_end = child_paths.end();
				child_paths_iterator_t child_itr = child_paths.begin();
				while(child_itr != child_end)
				{
					cwd_paths.merge(*child_itr);
					++child_itr;
				}
			}
		}
		if (as_thread)
		{
			p_thread_counter->Dec();
		}
	}
	bool FileFinder::fileExtMatch(const fs::path test)
	{
		if (m_ext == "*")
			return(true);
		else if (m_ext == test.extension())
			return(true);
		else
			return(false);
	}
}; //namespace jos

