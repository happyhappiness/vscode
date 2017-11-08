static void run_update_post_hook(struct command *commands)
{
	struct command *cmd;
	int argc;
	struct child_process proc = CHILD_PROCESS_INIT;
	const char *hook;

	hook = find_hook("post-update");
	for (argc = 0, cmd = commands; cmd; cmd = cmd->next) {
		if (cmd->error_string || cmd->did_not_exist)
			continue;
		argc++;
	}
	if (!argc || !hook)
		return;

	argv_array_push(&proc.args, hook);
	for (cmd = commands; cmd; cmd = cmd->next) {
		if (cmd->error_string || cmd->did_not_exist)
			continue;
		argv_array_push(&proc.args, cmd->ref_name);
	}

	proc.no_stdin = 1;
	proc.stdout_to_stderr = 1;
	proc.err = use_sideband ? -1 : 0;

	if (!start_command(&proc)) {
		if (use_sideband)
			copy_to_sideband(proc.err, -1, NULL);
		finish_command(&proc);
	}
}