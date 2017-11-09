static int wait_all(void)
{
	int hit = 0;
	int i;

	grep_lock();
	all_work_added = 1;

	/* Wait until all work is done. */
	while (todo_done != todo_end)
		pthread_cond_wait(&cond_result, &grep_mutex);

	/* Wake up all the consumer threads so they can see that there
	 * is no more work to do.
	 */
	pthread_cond_broadcast(&cond_add);
	grep_unlock();

	for (i = 0; i < num_threads; i++) {
		void *h;
		pthread_join(threads[i], &h);
		hit |= (int) (intptr_t) h;
	}

	free(threads);

	pthread_mutex_destroy(&grep_mutex);
	pthread_mutex_destroy(&grep_read_mutex);
	pthread_mutex_destroy(&grep_attr_mutex);
	pthread_cond_destroy(&cond_add);
	pthread_cond_destroy(&cond_write);
	pthread_cond_destroy(&cond_result);
	grep_use_locks = 0;

	return hit;
}