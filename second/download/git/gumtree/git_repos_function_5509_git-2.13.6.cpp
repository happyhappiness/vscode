static void resolve_deltas(void)
{
	int i;

	if (!nr_ofs_deltas && !nr_ref_deltas)
		return;

	/* Sort deltas by base SHA1/offset for fast searching */
	QSORT(ofs_deltas, nr_ofs_deltas, compare_ofs_delta_entry);
	QSORT(ref_deltas, nr_ref_deltas, compare_ref_delta_entry);

	if (verbose || show_resolving_progress)
		progress = start_progress(_("Resolving deltas"),
					  nr_ref_deltas + nr_ofs_deltas);

#ifndef NO_PTHREADS
	nr_dispatched = 0;
	if (nr_threads > 1 || getenv("GIT_FORCE_THREADS")) {
		init_thread();
		for (i = 0; i < nr_threads; i++) {
			int ret = pthread_create(&thread_data[i].thread, NULL,
						 threaded_second_pass, thread_data + i);
			if (ret)
				die(_("unable to create thread: %s"),
				    strerror(ret));
		}
		for (i = 0; i < nr_threads; i++)
			pthread_join(thread_data[i].thread, NULL);
		cleanup_thread();
		return;
	}
#endif

	for (i = 0; i < nr_objects; i++) {
		struct object_entry *obj = &objects[i];

		if (is_delta_type(obj->type))
			continue;
		resolve_base(obj);
		display_progress(progress, nr_resolved_deltas);
	}
}