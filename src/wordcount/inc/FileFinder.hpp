/* vim: tabstop=4:softtabstop=4:shiftwidth=4:noexpandtab
 * =====================================================================================
 *
 *       Filename:  FileFinder.hpp
 *
 *    Description:  Multi-threaded class to find all files in a directory path.
 *
 *        Version:  1.0
 *        Created:  09/14/2013 13:03:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Suykerbuyk
 *   Organization:  SolidFire
 *
 * =====================================================================================
 */
#ifndef JOS_FILE_FINDER_GUARD
#define JOS_FILE_FINDER_GUARD

#include <boost/filesystem.hpp>

namespace jos
{
	class ThreadCounter;

	namespace fs = boost::filesystem;
	typedef std::list<fs::path> file_path_list_t;
	typedef std::list<fs::path>::iterator file_path_list_itr_t;
	typedef std::list<fs::path>::const_iterator file_path_list_const_itr_t;
	
	/**
	 * @brief - Simple class to recursively find all files in a path.
	 */
	class FileFinder
	{
		public:
			/**
			 * @brief Constructor
			 */
			FileFinder();
			/**
			 * @brief Destructor
			 */
			virtual ~FileFinder();
			/**
			 * @brief Function to find all matching files in the provided path.
			 *
			 * @param aDir - Directory to start recursively searching from.
			 * @param cwd_paths - std::list of boost::filesystem::paths found.
			 */
			void Find(fs::path aDir, jos::file_path_list_t& cwd_paths, std::string file_extension="*");
		private:
			bool fileExtMatch(const fs::path test);
			void findFiles(fs::path aDir, jos::file_path_list_t& cwd_paths, bool as_thread);
			ThreadCounter* p_thread_counter;
			std::string    m_ext;
	};// class FileFinder
}; //namespace jos
#endif //JOS_FILE_FINDER_GUARD

