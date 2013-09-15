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
#include <boost/filesystem.hpp>
#include <boost/unordered_map.hpp>
#include "FileFinder.hpp"

using namespace jos;

struct cmp_result_items : public std::binary_function<int, std::string, bool>
{
	bool  operator() (const int& a, const int& b) const { return (a > b); }
	bool  operator() (const std::string& a, const std::string& b) const { return (a < b); }
};
void test(const boost::filesystem::path& path)
{
	//typedef boost::unorderedmap<std::string, int> word_counter_t;
	typedef std::map<std::string, int> word_counter_t;
	typedef word_counter_t::iterator word_counter_itr_t;

	typedef std::multimap<int, std::string, cmp_result_items> result_t;
	typedef std::multimap<int, std::string, cmp_result_items>::iterator result_itr_t;

	word_counter_t wc;
	result_t result;

	std::ifstream file;
	file.open(path.string().c_str());
	if (file)
	{
		std::string line;
		while (std::getline(file, line))
		{
			std::string::iterator end=line.end();
			std::string::iterator itr=line.begin();
			std::string::iterator word_start=line.end();
			// This not safe for unicode, but boost::algorithm::to_lower is SLOW!!
			std::transform(line.begin(), line.end(), line.begin(), ::tolower);
			while (itr != end)
			{
				if (*itr < 0 || (!std::isalnum(*itr) && *itr != '_'))
				{
					if (word_start != end)
					{
						++wc[std::string(word_start, itr)];
					}
					word_start = end;
				}
				else if (word_start == end)
				{
					word_start = itr;
				}
				++itr;
			}
			if (word_start != end)
			{
				++wc[std::string(word_start, itr)];
			}
		}
	}
	word_counter_itr_t wc_itr = wc.begin();
	while (wc_itr != wc.end())
	{
		result.insert(std::make_pair(wc_itr->second, wc_itr->first));
		wc_itr++;
	}
	result_itr_t result_itr = result.begin();
	while (result_itr != result.end())
	{
	    std::cout << std::setw(7) << std::setiosflags(std::ios::right) << result_itr->first << ": " << result_itr->second << std::endl;
		result_itr++;
	}
}

int main(int argc, char* argv[])
{
	boost::filesystem::path path("txt/test.txt");
	//boost::filesystem::path path("txt/life.on.the.mississippi.txt");
	test(path);

//	path_list_cwd_t paths;
//	FileFinder finder;
//	finder.Find(boost::filesystem::path("."), paths, ".txt");
//
//	path_list_cwd_iterator_t path_end=paths.end();
//	path_list_cwd_iterator_t path_itr=paths.begin();
//	while (path_itr != path_end)
//	{
//		std::cout << boost::filesystem::canonical(*path_itr) << std::endl;
//		++path_itr;
//	}
	return 0;
}

