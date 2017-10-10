	argv_array_pushf(&helper->args, "git-remote-%s", data->name);
	argv_array_push(&helper->args, transport->remote->name);
	argv_array_push(&helper->args, remove_ext_force(transport->url));
	helper->git_cmd = 0;
	helper->silent_exec_failure = 1;

	if (have_git_dir())
		argv_array_pushf(&helper->env_array, "%s=%s",
				 GIT_DIR_ENVIRONMENT, get_git_dir());

	code = start_command(helper);
	if (code < 0 && errno == ENOENT)
		die("Unable to find remote helper for '%s'", data->name);
	else if (code != 0)
		exit(code);
