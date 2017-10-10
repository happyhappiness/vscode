				free(hostandport);
				free(path);
				free(conn);
				return NULL;
			}

			ssh = get_ssh_command();
			if (!ssh) {
				const char *base;
				char *ssh_dup;

				/*
