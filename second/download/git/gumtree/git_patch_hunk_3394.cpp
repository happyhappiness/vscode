 				free(hostandport);
 				free(path);
 				free(conn);
 				return NULL;
 			}
 
-			if (looks_like_command_line_option(ssh_host))
-				die("strange hostname '%s' blocked", ssh_host);
-
 			ssh = getenv("GIT_SSH_COMMAND");
 			if (!ssh) {
 				const char *base;
 				char *ssh_dup;
 
 				/*
