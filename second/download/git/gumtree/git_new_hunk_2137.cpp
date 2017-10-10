				*envchanged = 1;
		} else if (!strcmp(cmd, "-C")) {
			if (*argc < 2) {
				fprintf(stderr, "No directory given for -C.\n" );
				usage(git_usage_string);
			}
			if ((*argv)[1][0]) {
				if (chdir((*argv)[1]))
					die_errno("Cannot change to '%s'", (*argv)[1]);
				if (envchanged)
					*envchanged = 1;
			}
			(*argv)++;
			(*argc)--;
		} else {
			fprintf(stderr, "Unknown option: %s\n", cmd);
			usage(git_usage_string);
		}
