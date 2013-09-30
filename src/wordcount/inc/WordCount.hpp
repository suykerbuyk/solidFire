/* vim: tabstop=4:softtabstop=4:shiftwidth=4:noexpandtab
 * =====================================================================================
 *
 *       Filename:  WordCount.hpp
 *
 *    Description:  Defines WordCount Class
 *
 *        Version:  1.0
 *        Created:  09/16/2013 10:12:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef JOS_WORDCOUNT_GUARD
#define JOS_WORDCOUNT_GUARD

//#include <iostream>
//#include <iomanip>
#include <fstream>
#include <cstddef>
#include <map>
//#include <boost/unordered_map.hpp>
#include "FileFinder.hpp"

namespace jos
{
	struct word_count_comparator : public std::binary_function<int, std::string, bool>
	{
		bool  operator() (const int& a, const int& b) const { return (a > b); }
		bool  operator() (const std::string& a, const std::string& b) const { return (a < b); }
	};
	typedef std::multimap<int, std::string, word_count_comparator> word_counts_t;
	typedef std::multimap<int, std::string, word_count_comparator>::iterator word_counts_itr_t;
	typedef std::multimap<int, std::string, word_count_comparator>::const_iterator word_counts_const_itr_t;

	class WordCount
	{
		public:
			class Impl;
			WordCount();
			virtual ~WordCount();
			
			void CountWords(const boost::filesystem::path& path);
			void CountWords(const file_path_list_t& paths);
			void GetTotals(word_counts_t& word_counts);
		private:
			Impl* p_impl;

	};
};
#endif // JOS_WORDCOUNT_GUARD
