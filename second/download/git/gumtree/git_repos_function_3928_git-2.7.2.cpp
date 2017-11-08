int main(int argc, char **argv)
{
	char *prog;
	const char **user_argv;
	struct commands *cmd;
	int count;

	git_setup_gettext();

	git_extract_argv0_path(argv[0]);

	/*
	 * Always open file descriptors 0/1/2 to avoid clobbering files
	 * in die().  It also avoids messing up when the pipes are dup'ed
	 * onto stdin/stdout/stderr in the child processes we spawn.
	 */
	sanitize_stdfds();

	/*
	 * Special hack to pretend to be a CVS server
	 */
	if (argc == 2 && !strcmp(argv[1], "cvs server")) {
		argv--;
	} else if (argc == 1) {
		/* Allow the user to run an interactive shell */
		cd_to_homedir();
		if (access(COMMAND_DIR, R_OK | X_OK) == -1) {
			die("Interactive git shell is not enabled.\n"
			    "hint: ~/" COMMAND_DIR " should exist "
			    "and have read and execute access.");
		}
		run_shell();
		exit(0);
	} else if (argc != 3 || strcmp(argv[1], "-c")) {
		/*
		 * We do not accept any other modes except "-c" followed by
		 * "cmd arg", where "cmd" is a very limited subset of git
		 * commands or a command in the COMMAND_DIR
		 */
		die("Run with no arguments or with -c cmd");
	}

	prog = xstrdup(argv[2]);
	if (!strncmp(prog, "git", 3) && isspace(prog[3]))
		/* Accept "git foo" as if the caller said "git-foo". */
		prog[3] = '-';

	for (cmd = cmd_list ; cmd->name ; cmd++) {
		int len = strlen(cmd->name);
		char *arg;
		if (strncmp(cmd->name, prog, len))
			continue;
		arg = NULL;
		switch (prog[len]) {
		case '\0':
			arg = NULL;
			break;
		case ' ':
			arg = prog + len + 1;
			break;
		default:
			continue;
		}
		exit(cmd->exec(cmd->name, arg));
	}

	cd_to_homedir();
	count = split_cmdline(prog, &user_argv);
	if (count >= 0) {
		if (is_valid_cmd_name(user_argv[0])) {
			prog = make_cmd(user_argv[0]);
			user_argv[0] = prog;
			execv(user_argv[0], (char *const *) user_argv);
		}
		free(prog);
		free(user_argv);
		die("unrecognized command '%s'", argv[2]);
	} else {
		free(prog);
		die("invalid command format '%s': %s", argv[2],
		    split_cmdline_strerror(count));
	}
}