static void start_threads(struct grep_opt *opt)
{
	int i;

	pthread_mutex_init(&grep_mutex, NULL);
	pthread_mutex_init(&grep_read_mutex, NULL);
	pthread_mutex_init(&grep_attr_mutex, NULL);
	pthread_cond_init(&cond_add, NULL);
	pthread_cond_init(&cond_write, NULL);
	pthread_cond_init(&cond_result, NULL);
	grep_use_locks = 1;

	for (i = 0; i < ARRAY_SIZE(todo); i++) {
		strbuf_init(&todo[i].out, 0);
	}

	threads = xcalloc(num_threads, sizeof(*threads));
	for (i = 0; i < num_threads; i++) {
		int err;
		struct grep_opt *o = grep_opt_dup(opt);
		o->output = strbuf_out;
		if (i)
			o->debug = 0;
		compile_grep_patterns(o);
		err = pthread_create(&threads[i], NULL, run, o);

		if (err)
			die(_("grep: failed to create thread: %s"),
			    strerror(err));
	}
}