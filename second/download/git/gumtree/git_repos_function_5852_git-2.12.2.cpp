static int grep_submodule_launch(struct grep_opt *opt,
				 const struct grep_source *gs)
{
	struct child_process cp = CHILD_PROCESS_INIT;
	int status, i;
	const char *end_of_base;
	const char *name;
	struct work_item *w = opt->output_priv;

	end_of_base = strchr(gs->name, ':');
	if (gs->identifier && end_of_base)
		name = end_of_base + 1;
	else
		name = gs->name;

	prepare_submodule_repo_env(&cp.env_array);
	argv_array_push(&cp.env_array, GIT_DIR_ENVIRONMENT);

	/* Add super prefix */
	argv_array_pushf(&cp.args, "--super-prefix=%s%s/",
			 super_prefix ? super_prefix : "",
			 name);
	argv_array_push(&cp.args, "grep");

	/*
	 * Add basename of parent project
	 * When performing grep on a tree object the filename is prefixed
	 * with the object's name: 'tree-name:filename'.  In order to
	 * provide uniformity of output we want to pass the name of the
	 * parent project's object name to the submodule so the submodule can
	 * prefix its output with the parent's name and not its own SHA1.
	 */
	if (gs->identifier && end_of_base)
		argv_array_pushf(&cp.args, "--parent-basename=%.*s",
				 (int) (end_of_base - gs->name),
				 gs->name);

	/* Add options */
	for (i = 0; i < submodule_options.argc; i++) {
		/*
		 * If there is a tree identifier for the submodule, add the
		 * rev after adding the submodule options but before the
		 * pathspecs.  To do this we listen for the '--' and insert the
		 * sha1 before pushing the '--' onto the child process argv
		 * array.
		 */
		if (gs->identifier &&
		    !strcmp("--", submodule_options.argv[i])) {
			argv_array_push(&cp.args, sha1_to_hex(gs->identifier));
		}

		argv_array_push(&cp.args, submodule_options.argv[i]);
	}

	cp.git_cmd = 1;
	cp.dir = gs->path;

	/*
	 * Capture output to output buffer and check the return code from the
	 * child process.  A '0' indicates a hit, a '1' indicates no hit and
	 * anything else is an error.
	 */
	status = capture_command(&cp, &w->out, 0);
	if (status && (status != 1)) {
		/* flush the buffer */
		write_or_die(1, w->out.buf, w->out.len);
		die("process for submodule '%s' failed with exit code: %d",
		    gs->name, status);
	}

	/* invert the return code to make a hit equal to 1 */
	return !status;
}