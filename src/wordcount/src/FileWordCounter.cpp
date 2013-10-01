/*  vim: tabstop=4:softtabstop=4:shiftwidth=4:noexpandtab
 * =====================================================================================
 *
 *       Filename:  FileWordCounter.cpp
 *
 *    Description:  Interface to functionality that can count words in files.
 *
 *        Version:  1.0
 *        Created:  09/30/2013 18:45:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "WordCount.hpp"
#include "FileFinder.hpp"
#include "ThreadCounter.hpp"
#include "FileWordCounter.hpp"
#include "jos_types.hpp"

using namespace jos;
class FileWordCounter::Impl
{
	public:
		Impl(void) : m_ext(".txt"), m_path(".") {}
		virtual ~Impl() {}
		void   SetFileExtension(const std::string& ext)  {m_ext = ext;}
		void   SetRootPath     (const std::string& path) {m_path = path;}
		void   SetMaxThreads   (const size_t& max_count) {tc.SetMaxThreads(max_count);}
		const std::string& GetFileExtension(void) {return(m_ext);}
		const std::string& GetRootPath     (void) {return(fs::canonical(m_path).string());}
		size_t             GetMaxThreads   (void) {return(tc.GetMaxThreads());}
		void  GetFileList(file_path_list_t& paths)
		{
			ff.Find(m_path, paths, m_ext);
		}
		void  GetWordCounts(file_path_list_t& paths, word_counts_t& word_counts)
		{
			wc.CountWords(paths);
			wc.GetTotals(word_counts);
		}

	private:
		std::string   m_ext;
		fs::path      m_path;
		WordCount     wc;
		FileFinder    ff;
		ThreadCounter tc;
};

FileWordCounter::FileWordCounter(void)
{
	p_impl = new FileWordCounter::Impl();
}
FileWordCounter::~FileWordCounter(void)
{
	delete p_impl;
}
void FileWordCounter::GetWordCounts(word_counts_t& word_counts)
{
	file_path_list_t paths;
	p_impl->GetFileList(paths);
	p_impl->GetWordCounts(paths, word_counts);
}
void FileWordCounter::SetRootPath     (const std::string& path)
{
	p_impl->SetRootPath(path);
}
void FileWordCounter::SetFileExtension(const std::string& ext)
{
	p_impl->SetFileExtension(ext);
}
void FileWordCounter::SetMaxThreads   (const size_t& max_count)
{
	p_impl->SetMaxThreads(max_count);
}
const std::string& FileWordCounter::GetRootPath(void)
{
	return p_impl->GetRootPath();
}
const std::string& FileWordCounter::GetFileExtension(void)
{
	return p_impl->GetFileExtension();
}
size_t FileWordCounter::GetMaxThreads()
{
	return p_impl->GetMaxThreads();
}
