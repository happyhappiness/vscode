				free(hostandport);
				free(path);
				free(conn);
				return NULL;
			}

			if (looks_like_command_line_option(ssh_host))
				die("strange hostname '%s' blocked", ssh_host);

			ssh = get_ssh_command();
			if (!ssh) {
				const char *base;
				char *ssh_dup;

				/*
				 * GIT_SSH is the no-shell version of
				 * GIT_SSH_COMMAND (and must remain so for
				 * historical compatibility).
				 */
				conn->use_shell = 0;

				ssh = getenv("GIT_SSH");
				if (!ssh)
					ssh = "ssh";

				ssh_dup = xstrdup(ssh);
				base = basename(ssh_dup);

				tortoiseplink = !strcasecmp(base, "tortoiseplink") ||
					!strcasecmp(base, "tortoiseplink.exe");
				putty = tortoiseplink ||
					!strcasecmp(base, "plink") ||
					!strcasecmp(base, "plink.exe");

				free(ssh_dup);
			}

			argv_array_push(&conn->args, ssh);
			if (flags & CONNECT_IPV4)
				argv_array_push(&conn->args, "-4");
			else if (flags & CONNECT_IPV6)
				argv_array_push(&conn->args, "-6");
			if (tortoiseplink)
				argv_array_push(&conn->args, "-batch");
			if (port) {
				/* P is for PuTTY, p is for OpenSSH */
				argv_array_push(&conn->args, putty ? "-P" : "-p");
				argv_array_push(&conn->args, port);
			}
			argv_array_push(&conn->args, ssh_host);
		} else {
			transport_check_allowed("file");
		}
