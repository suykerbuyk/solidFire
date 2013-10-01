/*  vim: tabstop=4:softtabstop=4:shiftwidth=4:noexpandtab
 * =====================================================================================
 *
 *       Filename:  ThreadCounter.cpp
 *
 *    Description:  Implimentation of ThreadCounter
 *
 *        Version:  1.0
 *        Created:  09/14/2013 10:26:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Suykerbuyk
 *   Organization:  SolidFire
 *
 * =====================================================================================
 */
#include <boost/thread.hpp>
#include <boost/date_time.hpp>
#include "ThreadCounter.hpp"

using namespace jos;

#ifndef MAX_CONCURRENT_THREADS
#	define MAX_CONCURRENT_THREADS 64
#endif 

size_t ThreadCounter::m_max_threads = MAX_CONCURRENT_THREADS;
size_t ThreadCounter::m_thread_count = 0;
boost::mutex thread_count_mutex;

size_t ThreadCounter::Get(void)
{
	boost::mutex::scoped_lock lock( thread_count_mutex );
	return (m_thread_count);
}
size_t ThreadCounter::Dec(void)
{
	boost::mutex::scoped_lock lock( thread_count_mutex );
	m_thread_count--;
	//std::cout << "Thread Dec Count: " << m_thread_count << std::endl;
	return (m_thread_count);
}
size_t ThreadCounter::Inc(void)
{
	int ms_to_wait     = 10;
	int ms_time_waited = 0;
	const int ms_max_wait_time = 1000;
	while ( 1 )
	{
		boost::mutex::scoped_lock lock( thread_count_mutex );
		if ( m_thread_count >= m_max_threads )
		{
			ms_time_waited += ms_to_wait;
			boost::this_thread::sleep
				(boost::posix_time::milliseconds(ms_to_wait));
			if ( ms_time_waited >= ms_max_wait_time )
			{
				std::cerr << "Not enough available threads to continue!" << std::endl;
				std::cerr << "  Waited " 
					<< ms_time_waited << "ms for one of " 
					<< m_thread_count << " to become available" << std::endl;
				exit (1);
			}
		}
		else
		{
			break;
		}
	}
	boost::mutex::scoped_lock lock( thread_count_mutex );
	m_thread_count++;
	//std::cout << "Thread Inc Count: " << m_thread_count << std::endl;
	return (m_thread_count);
}
size_t ThreadCounter::TryInc(void)
{
	boost::mutex::scoped_lock lock( thread_count_mutex );
	if (m_thread_count < m_max_threads)
	{
		m_thread_count++;
		//std::cout << "Thread Try Count: " << m_thread_count << std::endl;
		return (m_thread_count);
	}
	else
	{
		//std::cout << "Thread NOP Count: " << m_thread_count << std::endl;
		return (0);
	}
}
void ThreadCounter::SetMaxThreads(size_t max_threads)
{
	boost::mutex::scoped_lock lock( thread_count_mutex );
	m_max_threads = max_threads;
}
size_t ThreadCounter::GetMaxThreads(void)
{
	return(m_max_threads);
}
