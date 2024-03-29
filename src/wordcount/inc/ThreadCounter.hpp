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
#ifndef JOS_THREAD_COUNTER_GUARD
#define JOS_THREAD_COUNTER_GUARD


namespace jos
{
	class ThreadCounter
	{
		public:
			size_t Get   (void);
			/**
			 * @brief - Decrements the number of active threads.
			 * May block execution if another thread is accessing thread count.
			 *
			 * @return - Returns the number of active threads.
			 */
			size_t Dec   (void);
			/**
			 * @brief - Increments the number of active threads.
			 * May temporarily block execution if another thread is manipulating thread count.
			 * Will block indefinitely if the thread count has reached max_threads.
			 *
			 * @return - Returns the updated number of active threads.
			 */
			size_t Inc   (void);
			/**
			 * @brief Attempts to increment the thread count.
			 * May temporarily block execution if another thread is manipulating thread count.
			 * Will return '0' if thread count has reached 'max_threads'.
			 *
			 * @return - Returns the updated number of active threads.
			 */
			size_t TryInc(void);
			/**
			 * @brief Modifies the maximum number of allowable threads.
			 *
			 * @param max_threads - Maximum thread count.
			 */
			void   SetMaxThreads(size_t max_threads);
			/**
			 * @brief Retrieves the maximum number of allowable threads.
			 *
			 */
			size_t GetMaxThreads(void);
		private:
			static size_t        m_max_threads;
			static size_t        m_thread_count;
	};
	
};

#endif // JOS_THREAD_COUNTER_GUARD

