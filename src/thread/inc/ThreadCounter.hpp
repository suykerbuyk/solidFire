/*  vim: tabstop=4:softtabstop=4:shiftwidth=4:noexpandtab
 * =====================================================================================
 *
 *       Filename:  ThreadCounter.hpp
 *
 *    Description:  Simple class to count and limit the number of concurrent threads.
 *                  My experiments on BSD using default stack settings found
 *                  an upper limit of ~600 threads at any one time by single
 *                  process on an otherwise lightly loaded system.
 *                  This class can be used to 'throttle' the number of threads.
 *
 *        Version:  1.0
 *        Created:  09/14/2013 09:40:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Suykerbuyk
 *   Organization:  SolidFire
 *
 * =====================================================================================
 */

#ifndef MAX_CONCURRENT_THREADS
#	define MAX_CONCURRENT_THREADS 256
#endif 

class boost::mutex;

namespace jos
{
	class ThreadCounter
	{
		public:
			ThreadCounter(size_t max_theads = MAX_CONCURRENT_THREADS);
			virtual ~ThreadCounter(void);
			size_t Get   (void);
			size_t Dec   (void);
			size_t Inc   (void);
			size_t TryInc(void);
		private:
			size_t        m_max_threads;
			size_t        m_thread_count;
			boost::mutex* p_mutex;
	};
	
};

