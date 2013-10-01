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
#include <boost/program_options.hpp>
#include "FileWordCounter.hpp"

int main(int argc, char* argv[])
{
	jos::FileWordCounter fwc;
	jos::word_counts_t wc;
	int words_to_print = 0;
	int thread_count   = 0;
	std::string path;
	std::string ext;

	namespace po = boost::program_options;
	po::options_description desc("WordCount Options");
	desc.add_options()
		("help,h",   "Print help messages")
		("path,p",    po::value<std::string>(&path)->default_value("."),\
		             "Path to search for files.")
		("ext,e",     po::value<std::string>(&ext)->default_value(".txt"), \
		             "File extensions to count words in.")
		("words,w",   po::value<int>(&words_to_print)->default_value(10),\
		             "The maximum number of words to display")
		("threads,t", po::value<int>(&thread_count)->default_value(128),\
		             "The number of threads to run at the same time");
	po::variables_map vm; 
	try
	{
		po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);
		if ( vm.count("help")  ) 
		{ 
			std::cout << "SolidFire Word Counter Demo App" << std::endl << desc << std::endl; 
			return 0; 
		}
		po::notify(vm);
		fwc.SetFileExtension(ext);
		fwc.SetRootPath(path);
		fwc.SetMaxThreads(thread_count);
	}
	catch(po::error& e) 
    { 
      std::cerr << "ERROR: " << e.what() << std::endl << std::endl; 
	  std::cerr << desc << std::endl;
      return 1;
    } 

	fwc.GetWordCounts(wc);

	jos::word_counts_itr_t wc_itr = wc.begin();
	while((wc_itr != wc.end()) && --words_to_print)
	{
	    std::cout << std::setw(7) << std::setiosflags(std::ios::right) << wc_itr->first << ": " << wc_itr->second << std::endl;
		++wc_itr;
	}
	return 0;
}

