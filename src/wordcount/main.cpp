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
#include "FileWordCounter.hpp"

int main(int argc, char* argv[])
{
	jos::FileWordCounter fwc;
	jos::word_counts_t wc;
	fwc.GetWordCounts(wc);

	jos::word_counts_itr_t wc_itr = wc.begin();
	while(wc_itr != wc.end())
	{
	    std::cout << std::setw(7) << std::setiosflags(std::ios::right) << wc_itr->first << ": " << wc_itr->second << std::endl;
		++wc_itr;
	}

//	jos::word_counts_t word_counts;
//	jos::file_path_list_t paths;
//	
//	jos::WordCount wc;
//	jos::FileFinder finder;
//
//	finder.Find(boost::filesystem::path("."), paths, ".txt");
//
//	jos::file_path_list_itr_t path_end=paths.end();
//	jos::file_path_list_itr_t path_itr=paths.begin();
//	while (path_itr != path_end)
//	{
//		std::cout << boost::filesystem::canonical(*path_itr) << std::endl;
//		++path_itr;
//	}
//	wc.CountWords(paths);
//	wc.GetTotals(word_counts);
//	jos::word_counts_itr_t ret_itr = word_counts.begin();
//	while (ret_itr != word_counts.end())
//	{
//	    std::cout << std::setw(7) << std::setiosflags(std::ios::right) << ret_itr->first << ": " << ret_itr->second << std::endl;
//		ret_itr++;
//	}
	return 0;
}

