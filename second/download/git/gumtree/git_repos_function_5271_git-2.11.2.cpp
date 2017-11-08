static void *threaded_second_pass(void *data)
{
	set_thread_data(data);
	for (;;) {
		int i;
		counter_lock();
		display_progress(progress, nr_resolved_deltas);
		counter_unlock();
		work_lock();
		while (nr_dispatched < nr_objects &&
		       is_delta_type(objects[nr_dispatched].type))
			nr_dispatched++;
		if (nr_dispatched >= nr_objects) {
			work_unlock();
			break;
		}
		i = nr_dispatched++;
		work_unlock();

		resolve_base(&objects[i]);
	}
	return NULL;
}