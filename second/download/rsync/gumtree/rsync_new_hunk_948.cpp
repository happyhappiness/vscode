			rprintf(FERROR, "internal: args[] overflowed in do_cmd()\n");
			exit_cleanup(RERR_SYNTAX);
		}
		if (strncmp(*argv, modname, modlen) == 0
		 && argv[0][modlen] == '\0')
			sargs[sargc++] = modname; /* we send "modname/" */
		else if (**argv == '-') {
			if (asprintf(sargs + sargc++, "./%s", *argv) < 0)
				out_of_memory("start_inband_exchange");
		} else
			sargs[sargc++] = *argv;
		argv++;
		argc--;
	}

	sargs[sargc] = NULL;
