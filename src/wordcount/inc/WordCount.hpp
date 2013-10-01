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

#include "jos_types.hpp"

namespace jos
{

	class WordCount
	{
		public:
			WordCount();
			virtual ~WordCount();
			
			void CountWords(const boost::filesystem::path& path);
			void CountWords(const file_path_list_t& paths);
			void GetTotals(word_counts_t& word_counts);
		protected:
			class Impl;
		private:
			Impl* p_impl;

	};
};
#endif // JOS_WORDCOUNT_GUARD
