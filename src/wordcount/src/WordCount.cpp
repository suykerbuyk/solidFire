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

#include <fstream>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include "WordCount.hpp"
#include "ThreadCounter.hpp"

using namespace jos;

#ifndef MAX_CONCURRENT_THREADS
#	define MAX_CONCURRENT_THREADS 128
#endif 
//
//typedef boost::unorderedmap<std::string, int> file_word_counter_t;
typedef std::map<std::string, int> file_word_counter_t;
typedef std::map<std::string, int>::iterator file_word_counter_itr_t;


class WordCount::Impl
{
	public:
		Impl(void) {}
		virtual ~Impl() {}
		void AddFileContents(const boost::filesystem::path& path);
		void WaitForCompletion(void)
		{
			m_threads.join_all();
		}
		void GetTotals(word_counts_t& ret);
	private:
		void countFileWords(const boost::filesystem::path& path, bool asThread);
		boost::mutex         m_word_counter_mutex;
		file_word_counter_t  m_tally;
		boost::thread_group  m_threads;
		ThreadCounter        m_thread_counter;
};

void WordCount::Impl::GetTotals(word_counts_t& ret)
{
	ret.clear();
	WaitForCompletion();
	boost::mutex::scoped_lock lock (m_word_counter_mutex);
	file_word_counter_itr_t m_tally_itr = m_tally.begin();
	/*  transform from string ordered map to a map sorted by count */
	while (m_tally_itr != m_tally.end())
	{
		ret.insert(std::make_pair(m_tally_itr->second, m_tally_itr->first));
		++m_tally_itr;
	}

}
void WordCount::Impl::AddFileContents(const boost::filesystem::path& path)
{
		if (m_thread_counter.TryInc())
		{
			m_threads.create_thread(
					boost::bind(&WordCount::Impl::countFileWords, this, path, true));
		}
		else 
		{
			countFileWords(path, false);
		}
}
void WordCount::Impl::countFileWords(const boost::filesystem::path& path, bool asThread)
{
	std::ifstream word_file;
	std::locale locality("C");

	word_file.open(path.string().c_str());
	if (word_file)
	{

		file_word_counter_t file_wc;
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
		// Update the totals so far....
		boost::mutex::scoped_lock lock (m_word_counter_mutex);
		file_word_counter_itr_t file_wc_itr = file_wc.begin();
		while (file_wc_itr != file_wc.end())
		{
			m_tally[file_wc_itr->first] += file_wc_itr->second;
			++file_wc_itr;
		}
	}
	else
	{
		std::cerr << "Failed to read: " << path << std::endl;
	}
	if (asThread)
	{
		m_thread_counter.Dec();
	}
}


WordCount::WordCount()
{
	p_impl = new WordCount::Impl;

}
WordCount::~WordCount()
{
	delete p_impl;
}
void WordCount::CountWords(const file_path_list_t& paths)
{
	
	file_path_list_const_itr_t fp_itr = paths.begin();
	file_path_list_const_itr_t fp_end = paths.end();

	while(fp_itr != fp_end)
	{
		p_impl->AddFileContents(*fp_itr);
		++fp_itr;
	}
}
void WordCount::CountWords(const boost::filesystem::path& path)
{

	p_impl->AddFileContents(path);
}
void WordCount::GetTotals(word_counts_t& word_counts)
{
	p_impl->GetTotals(word_counts);
}
