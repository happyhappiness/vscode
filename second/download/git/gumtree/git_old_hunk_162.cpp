			      struct diff_filespec *two,
			      const char *xfrm_msg,
			      int complete_rewrite,
			      struct diff_options *o)
{
	struct argv_array argv = ARGV_ARRAY_INIT;
	int retval;
	struct diff_queue_struct *q = &diff_queued_diff;
	const char *env[3] = { NULL };
	char env_counter[50];
	char env_total[50];

	if (one && two) {
		struct diff_tempfile *temp_one, *temp_two;
		const char *othername = (other ? other : name);
		temp_one = prepare_temp_file(name, one);
		temp_two = prepare_temp_file(othername, two);
		argv_array_push(&argv, pgm);
		argv_array_push(&argv, name);
		argv_array_push(&argv, temp_one->name);
		argv_array_push(&argv, temp_one->hex);
		argv_array_push(&argv, temp_one->mode);
		argv_array_push(&argv, temp_two->name);
		argv_array_push(&argv, temp_two->hex);
		argv_array_push(&argv, temp_two->mode);
		if (other) {
			argv_array_push(&argv, other);
			argv_array_push(&argv, xfrm_msg);
		}
	} else {
		argv_array_push(&argv, pgm);
		argv_array_push(&argv, name);
	}
	fflush(NULL);

	env[0] = env_counter;
	snprintf(env_counter, sizeof(env_counter), "GIT_DIFF_PATH_COUNTER=%d",
		 ++o->diff_path_counter);
	env[1] = env_total;
	snprintf(env_total, sizeof(env_total), "GIT_DIFF_PATH_TOTAL=%d", q->nr);

	retval = run_command_v_opt_cd_env(argv.argv, RUN_USING_SHELL, NULL, env);
	remove_tempfile();
	argv_array_clear(&argv);
	if (retval) {
		fprintf(stderr, "external diff died, stopping at %s.\n", name);
		exit(1);
	}
}

static int similarity_index(struct diff_filepair *p)
{
	return p->score * 100 / MAX_SCORE;
}
