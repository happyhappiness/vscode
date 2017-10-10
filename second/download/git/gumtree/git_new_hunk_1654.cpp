	my_argv[1] = arg;
	my_argv[2] = NULL;

	return execv_git_cmd(my_argv);
}

static int is_valid_cmd_name(const char *cmd)
{
	/* Test command contains no . or / characters */
	return cmd[strcspn(cmd, "./")] == '\0';
}

