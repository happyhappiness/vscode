				printf("Diag: userandhost=%s\n", ssh_host ? ssh_host : "NULL");
				printf("Diag: port=%s\n", port ? port : "NONE");
				printf("Diag: path=%s\n", path ? path : "NULL");

				free(hostandport);
				free(path);
				return NULL;
			} else {
				ssh = getenv("GIT_SSH_COMMAND");
				if (ssh) {
					conn->use_shell = 1;
					putty = 0;
