	struct child_process *helper;
	const char **refspecs = NULL;
	int refspec_nr = 0;
	int refspec_alloc = 0;
	int duped;
	int code;

	if (data->helper)
		return data->helper;

	helper = xmalloc(sizeof(*helper));
	child_process_init(helper);
	helper->in = -1;
	helper->out = -1;
	helper->err = 0;
	argv_array_pushf(&helper->args, "git-remote-%s", data->name);
	argv_array_push(&helper->args, transport->remote->name);
	argv_array_push(&helper->args, remove_ext_force(transport->url));
	helper->git_cmd = 0;
	helper->silent_exec_failure = 1;

	argv_array_pushf(&helper->env_array, "%s=%s", GIT_DIR_ENVIRONMENT,
			 get_git_dir());

	code = start_command(helper);
	if (code < 0 && errno == ENOENT)
		die("Unable to find remote helper for '%s'", data->name);
	else if (code != 0)
		exit(code);
