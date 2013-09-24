/* vim: tabstop=4:softtabstop=4:shiftwidth=4:noexpandtab
 * =====================================================================================
 *
 *       Filename:  WordCount.cpp
 *
 *    Description:  Impliments a class to count word in a file or a list of files.
 *
 *        Version:  1.0
 *        Created:  09/15/2013 18:29:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Suykerbuyk
 *   Organization:  SolidFire
 *
 * =====================================================================================
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstddef>
#include <boost/thread.hpp>
#include "WordCount.hpp"
#include "ThreadCounter.hpp"

using namespace jos;

//typedef boost::unorderedmap<std::string, int> file_word_counter_t;
typedef std::map<std::string, int> file_word_counter_t;
typedef std::map<std::string, int>::iterator file_word_counter_itr_t;


class WordCountImpl
{
	public:
		WordCountImpl(file_word_counter_t& tally) :file_wc(tally) {};
	private:
		boost::mutex word_counter mutex;
		file_word_counter_t& file_wc;
};


std::size_t CountFileWords(const boost::filesystem::path& path, file_word_counter_t& file_wc)
{
	std::ifstream word_file;
	std::locale locality("C");

	word_file.open(path.string().c_str());
	if (word_file)
	{
		std::string line;
		while (std::getline(word_file, line))
		{
			std::string::iterator end=line.end();
			std::string::iterator itr=line.begin();
			std::string::iterator word_start=line.end();
			// This not safe for unicode, but boost::algorithm::to_lower is SLOW!!
			std::transform(line.begin(), line.end(), line.begin(), ::tolower);
			while (itr != end)
			{
				if (*itr < 0 || (!std::isalnum(*itr, locality) && *itr != '_'))
				{
					if (word_start != end)
					{
						++file_wc[std::string(word_start, itr)];
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
				++file_wc[std::string(word_start, itr)];
			}
		}
		word_file.close();
	}
	else
	{
		std::cerr << "Failed to read: " << path << std::endl;
	}
	return file_wc.size();
}


WordCount::WordCount()
{

}
WordCount::~WordCount()
{

}
void WordCount::Count(const file_path_list_t& paths, word_counts_t& ret)
{
	typedef std::vector<file_word_counter_t> word_count_lists_t;
	typedef std::vector<file_word_counter_t>::iterator word_count_lists_itr_t;
	typedef std::vector<file_word_counter_t>::const_iterator word_count_lists_const_itr_t;

	file_path_list_const_itr_t fp_itr = paths.begin();
	file_path_list_const_itr_t fp_end = paths.end();
	word_count_lists_t wc_lists;

	boost::thread_group threads;
	ThreadCounter thread_counter;


	while(fp_itr != fp_end)
	{
		file_word_counter_t file_wc;
		wc_lists.push_back(file_wc);
		if (thread_counter.TryInc())
		{
			threads.create_thread(
					boost::bind(CountFileWords, *fp_itr, boost::ref(wc_lists.back())));
		}
		else 
		{
			CountFileWords(*fp_itr, wc_lists.back());
		}
		++fp_itr;
	}
	threads.join_all();
	
	file_word_counter_t wc_totals;

	for (word_count_lists_itr_t wcl_itr = wc_lists.begin(); 
			wcl_itr < wc_lists.end(); 
			wcl_itr++)
	{
		for (file_word_counter_itr_t fwc_itr = wcl_itr->begin();
				fwc_itr != wcl_itr->end();
				++fwc_itr)
		{
			wc_totals[fwc_itr->first] += fwc_itr->second;
		}
	}	
	file_word_counter_itr_t wc_totals_itr = wc_totals.begin();
	while (wc_totals_itr != wc_totals.end())
	{
		ret.insert(std::make_pair(wc_totals_itr->second, wc_totals_itr->first));
		++wc_totals_itr;
	}
}
void WordCount::Count(const boost::filesystem::path& path, word_counts_t& ret)
{
	file_word_counter_t file_wc;

	CountFileWords(path, file_wc);
	
	file_word_counter_itr_t file_wc_itr = file_wc.begin();
	while (file_wc_itr != file_wc.end())
	{
		ret.insert(std::make_pair(file_wc_itr->second, file_wc_itr->first));
		file_wc_itr++;
	}
}

