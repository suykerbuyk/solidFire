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
	return 0;
}

