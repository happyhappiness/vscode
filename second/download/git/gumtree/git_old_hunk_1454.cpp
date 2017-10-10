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

		(*argv)++;
