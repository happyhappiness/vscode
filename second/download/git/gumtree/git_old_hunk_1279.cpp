
	threads = xcalloc(num_threads, sizeof(*threads));
	for (i = 0; i < num_threads; i++) {
		int err;
		struct grep_opt *o = grep_opt_dup(opt);
		o->output = strbuf_out;
		o->debug = 0;
		compile_grep_patterns(o);
		err = pthread_create(&threads[i], NULL, run, o);

		if (err)
			die(_("grep: failed to create thread: %s"),
			    strerror(err));
