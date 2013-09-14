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
#include <stdlib.h>
#include <boost/thread.hpp>

using namespace jos;

ThreadLimiter::ThreadLimiter(size_t max_theads = MAX_CONCURRENT_THREADS) : 
	m_max_threads(max_theads), 
	m_thread_count(0)
{
	p_mutex = new boost::mutex();
}
ThreadLimiter::~ThreadLimiter()
{
	delete p_mutex;
}
size_t ThreadLimiter::Get(void)
{
	boost::mutex::scoped_lock lock( *p_mutex );
	return (m_thread_count);
}
size_t ThreadLimiter::Dec(void)
{
	boost::mutex::scoped_lock lock( *p_mutex );
	m_thread_count--;
	return (m_thread_count);
}
size_t ThreadLimiter::Inc(void)
{
	boost::mutex::scoped_lock lock( *p_mutex );
	m_thread_count++;
	return (m_thread_count);
}
size_t ThreadLimiter::TryInc(void)
{
	boost::mutex::scoped_lock lock( *p_mutex );
	if (m_thread_count < m_max_threads)
	{
		m_thread_count++;
		return (m_thread_count);
	}
	else
	{
		return (0);
	}
}
