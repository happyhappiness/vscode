				free(hostandport);
				free(path);
				free(conn);
				return NULL;
			}

			ssh = getenv("GIT_SSH_COMMAND");
			if (!ssh) {
				const char *base;
				char *ssh_dup;

				/*
