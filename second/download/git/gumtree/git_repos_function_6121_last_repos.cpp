static struct work_item *get_work(void)
{
	struct work_item *ret;

	grep_lock();
	while (todo_start == todo_end && !all_work_added) {
		pthread_cond_wait(&cond_add, &grep_mutex);
	}

	if (todo_start == todo_end && all_work_added) {
		ret = NULL;
	} else {
		ret = &todo[todo_start];
		todo_start = (todo_start + 1) % ARRAY_SIZE(todo);
	}
	grep_unlock();
	return ret;
}