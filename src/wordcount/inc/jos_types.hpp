/* vim: tabstop=4:softtabstop=4:shiftwidth=4:noexpandtab
 * =====================================================================================
 *
 *       Filename:  jos_types.hpp
 *
 *    Description:  Common type defs
 *
 *        Version:  1.0
 *        Created:  09/30/2013 19:44:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Suykerbuyk
 *   Organization:  SolidFire
 *
 * =====================================================================================
 */
#ifndef JOS_TYPES_GUARD
#define JOS_TYPES_GUARD

#include <map>
#include <list>
#include <boost/filesystem.hpp>

namespace jos
{
	/**
	 * @brief Short cuts for commonly used namespaces
	 */
	namespace fs = boost::filesystem;
	
	/**
	 * @brief list containers for file paths
	 */
	typedef   std::list<fs::path> file_path_list_t;
	typedef   std::list<fs::path>::iterator file_path_list_itr_t;
	typedef   std::list<fs::path>::const_iterator file_path_list_const_itr_t;
	
	
	/**
	 * @brief Map container contains word counts.  Map sorts on word count, not the string words.
	 */
	struct word_count_comparator : public std::binary_function<int, std::string, bool>
	{
		bool  operator() (const int& a, const int& b) const { return (a > b); }
		bool  operator() (const std::string& a, const std::string& b) const { return (a < b); }
	};
	typedef std::multimap<int, std::string, word_count_comparator> word_counts_t;
	typedef std::multimap<int, std::string, word_count_comparator>::iterator word_counts_itr_t;
	typedef std::multimap<int, std::string, word_count_comparator>::const_iterator word_counts_const_itr_t;
};
#endif  // JOS_TYPES_GUARD

