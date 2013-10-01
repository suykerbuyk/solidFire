/*  vim: tabstop=4:softtabstop=4:shiftwidth=4:noexpandtab
 * =====================================================================================
 *
 *       Filename:  FileWordCounter.hpp
 *
 *    Description:  Interface class for functionaility to count file words.
 *
 *        Version:  1.0
 *        Created:  09/30/2013 18:45:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Suykerbuyk
 *   Organization:  SolidFire
 *
 * =====================================================================================
 */
#include <string>
#include "jos_types.hpp"

namespace jos 
{
	class FileWordCounter
	{
		public:
			FileWordCounter();
			virtual ~FileWordCounter();
			void  SetRootPath     (const std::string& path);
			void  SetFileExtension(const std::string& ext);
			void  SetMaxThreads   (const size_t& max_count);
			const std::string&   GetRootPath     (void);
			const std::string&   GetFileExtension(void);
			size_t               GetMaxThreads   (void);
			void  GetWordCounts(word_counts_t & word_counts);
		protected:
			class Impl;
		private:
			Impl* p_impl;
	};
};

