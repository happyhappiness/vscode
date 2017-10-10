				printf("Diag: path=%s\n", path ? path : "NULL");

				free(hostandport);
				free(path);
				free(conn);
				return NULL;
			}

			ssh = getenv("GIT_SSH_COMMAND");
			if (ssh) {
				conn->use_shell = 1;
				putty = 0;
			} else {
				const char *base;
				char *ssh_dup;

				ssh = getenv("GIT_SSH");
				if (!ssh)
					ssh = "ssh";

				ssh_dup = xstrdup(ssh);
				base = basename(ssh_dup);

				tortoiseplink = !strcasecmp(base, "tortoiseplink") ||
					!strcasecmp(base, "tortoiseplink.exe");
				putty = !strcasecmp(base, "plink") ||
					!strcasecmp(base, "plink.exe") || tortoiseplink;

				free(ssh_dup);
			}

			argv_array_push(&conn->args, ssh);
			if (tortoiseplink)
				argv_array_push(&conn->args, "-batch");
			if (port) {
				/* P is for PuTTY, p is for OpenSSH */
				argv_array_push(&conn->args, putty ? "-P" : "-p");
				argv_array_push(&conn->args, port);
			}
			argv_array_push(&conn->args, ssh_host);
		} else {
			/* remove repo-local variables from the environment */
			conn->env = local_repo_env;
			conn->use_shell = 1;
		}
		argv_array_push(&conn->args, cmd.buf);
