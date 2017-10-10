		done_alias = 1;
	}

	return done_alias;
}

int cmd_main(int argc, const char **argv)
{
	const char *cmd;
	int done_help = 0;

	cmd = argv[0];
	if (!cmd)
		cmd = "git-help";

	trace_command_performance(argv);

	/*
	 * "git-xxxx" is the same as "git xxxx", but we obviously:
	 *
	 *  - cannot take flags in between the "git" and the "xxxx".
