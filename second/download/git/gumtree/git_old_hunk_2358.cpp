				printf("Diag: path=%s\n", path ? path : "NULL");

				free(hostandport);
				free(path);
				free(conn);
				return NULL;
			} else {
				ssh = getenv("GIT_SSH_COMMAND");
				if (ssh) {
					conn->use_shell = 1;
					putty = 0;
				} else {
					ssh = getenv("GIT_SSH");
					if (!ssh)
						ssh = "ssh";
					putty = !!strcasestr(ssh, "plink");
				}

				argv_array_push(&conn->args, ssh);
				if (putty && !strcasestr(ssh, "tortoiseplink"))
					argv_array_push(&conn->args, "-batch");
				if (port) {
					/* P is for PuTTY, p is for OpenSSH */
					argv_array_push(&conn->args, putty ? "-P" : "-p");
					argv_array_push(&conn->args, port);
				}
				argv_array_push(&conn->args, ssh_host);
			}
		} else {
			/* remove repo-local variables from the environment */
			conn->env = local_repo_env;
			conn->use_shell = 1;
		}
		argv_array_push(&conn->args, cmd.buf);
