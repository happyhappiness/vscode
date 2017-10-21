			rprintf(FERROR, "internal: args[] overflowed in do_cmd()\n");
			exit_cleanup(RERR_SYNTAX);
		}
		if (strncmp(*argv, modname, modlen) == 0
		 && argv[0][modlen] == '\0')
			sargs[sargc++] = modname; /* we send "modname/" */
		else
			sargs[sargc++] = *argv;
		argv++;
		argc--;
	}

	sargs[sargc] = NULL;
