 				free(hostandport);
 				free(path);
 				free(conn);
 				return NULL;
 			}
 
-			if (looks_like_command_line_option(ssh_host))
-				die("strange hostname '%s' blocked", ssh_host);
-
 			ssh = get_ssh_command();
 			if (ssh)
 				handle_ssh_variant(ssh, 1, &port_option,
 						   &needs_batch);
 			else {
 				/*
