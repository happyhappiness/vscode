static void run_update_post_hook(struct command *commands)
{
	struct command *cmd;
	struct child_process proc = CHILD_PROCESS_INIT;
	const char *hook;

	hook = find_hook("post-update");
	if (!hook)
		return;

	for (cmd = commands; cmd; cmd = cmd->next) {
		if (cmd->error_string || cmd->did_not_exist)
			continue;
		if (!proc.args.argc)
			argv_array_push(&proc.args, hook);
		argv_array_push(&proc.args, cmd->ref_name);
	}
	if (!proc.args.argc)
		return;

	proc.no_stdin = 1;
	proc.stdout_to_stderr = 1;
	proc.err = use_sideband ? -1 : 0;

	if (!start_command(&proc)) {
		if (use_sideband)
			copy_to_sideband(proc.err, -1, NULL);
		finish_command(&proc);
	}
}