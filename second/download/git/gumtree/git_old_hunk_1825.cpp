			die("recursive alias: %s", alias_command);

		trace_argv_printf(new_argv,
				  "trace: alias expansion: %s =>",
				  alias_command);

		new_argv = xrealloc(new_argv, sizeof(char *) *
				    (count + *argcp));
		/* insert after command name */
		memcpy(new_argv + count, *argv + 1, sizeof(char *) * *argcp);

		*argv = new_argv;
		*argcp += count - 1;

