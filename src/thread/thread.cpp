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
#include <boost/thread.hpp>
#include <boost/filesystem.hpp>
#include <boost/date_time.hpp>

namespace fs = boost::filesystem;
namespace pt = boost::posix_time;

void findFiles(fs::path aDir)
{
	fs::directory_iterator end_iter;

	typedef std::multimap<std::time_t, fs::path> result_set_t;
	result_set_t result_set;

	if ( fs::exists(aDir) && fs::is_directory(aDir))
	{
		for( fs::directory_iterator dir_iter(aDir) ; \
				dir_iter != end_iter ; \
				++dir_iter)
			{
			if (fs::is_regular_file(dir_iter->status()) )
			{
				result_set.insert(\
						result_set_t::value_type(\
							fs::last_write_time(dir_iter->path()), \
							dir_iter->path())\
						);
				std::cout << dir_iter->path() << std::endl;
			}
		}
	}
}

void workerFunc()
{
	pt::seconds workTime(3);
	std::cout << "Worker: running" << std::endl;

	// Pretend to do something useful...
	boost::this_thread::sleep(workTime);
	std::cout << "Worker: finished" << std::endl;
}

int main(int argc, char* argv[])
{
	//findFiles(fs::path("/usr/home/johns"));
	findFiles(fs::path("."));
	std::cout << "main: startup" << std::endl;
	boost::thread workerThread(workerFunc);

	std::cout << "main: waiting for thread" << std::endl;
	workerThread.join();

	std::cout << "main: done" << std::endl;
	return 0;
}

