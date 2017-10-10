 		char *target_host = getenv("GIT_OVERRIDE_VIRTUAL_HOST");
 		if (target_host)
 			target_host = xstrdup(target_host);
 		else
 			target_host = xstrdup(hostandport);
 
+		transport_check_allowed("git");
+
 		/* These underlying connection commands die() if they
 		 * cannot connect.
 		 */
 		if (git_use_proxy(hostandport))
 			conn = git_proxy_connect(fd, hostandport);
 		else
