			}
			if (!strcmp(arg, "--is-bare-repository")) {
				printf("%s\n", is_bare_repository() ? "true"
						: "false");
				continue;
			}
			if (starts_with(arg, "--since=")) {
				show_datestring("--max-age=", arg+8);
				continue;
			}
			if (starts_with(arg, "--after=")) {
				show_datestring("--max-age=", arg+8);
