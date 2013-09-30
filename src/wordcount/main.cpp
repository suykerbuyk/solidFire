/* vim: tabstop=4:softtabstop=4:shiftwidth=4:noexpandtab
 * ===========================================================================
 *
 *       Filename:  thread.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  09/05/2013 11:45:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstddef>
#include "WordCount.hpp"
#include "FileFinder.hpp"


class FileWordCounter
{
	public:
		FileWordCounter() : m_ext(".txt"), m_path("."), m_tcnt(20) {}
		~FileWordCounter();
		void SetFileExtension(const std::string& ext)  {m_ext = ext;}
		void SetRootPath     (const std::string& path) {m_path = path;}
		void SetMaxThreads   (const size_t& max_count) {m_tcnt = max_count;}
	private:
		std::string m_ext;
		std::string m_path;
		size_t      m_tcnt;

};

int main(int argc, char* argv[])
{
	jos::word_counts_t word_counts;
	jos::file_path_list_t paths;
	
	jos::WordCount wc;
	jos::FileFinder finder;

	finder.Find(boost::filesystem::path("."), paths, ".txt");

	jos::file_path_list_itr_t path_end=paths.end();
	jos::file_path_list_itr_t path_itr=paths.begin();
	while (path_itr != path_end)
	{
		std::cout << boost::filesystem::canonical(*path_itr) << std::endl;
		++path_itr;
	}
	wc.CountWords(paths);
	wc.GetTotals(word_counts);
	jos::word_counts_itr_t ret_itr = word_counts.begin();
	while (ret_itr != word_counts.end())
	{
	    std::cout << std::setw(7) << std::setiosflags(std::ios::right) << ret_itr->first << ": " << ret_itr->second << std::endl;
		ret_itr++;
	}
	return 0;
}

