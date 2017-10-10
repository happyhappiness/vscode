 
 		if (regcomp(&re, c->pattern, REG_EXTENDED))
 			die("Bogus regex in service table: %s", c->pattern);
 		if (!regexec(&re, dir, 1, out, 0)) {
 			size_t n;
 
-			if (strcmp(method, c->method)) {
-				const char *proto = getenv("SERVER_PROTOCOL");
-				if (proto && !strcmp(proto, "HTTP/1.1")) {
-					http_status(405, "Method Not Allowed");
-					hdr_str("Allow", !strcmp(c->method, "GET") ?
-						"GET, HEAD" : c->method);
-				} else
-					http_status(400, "Bad Request");
-				hdr_nocache();
-				end_headers();
-				return 0;
-			}
+			if (strcmp(method, c->method))
+				return bad_request(&hdr, c);
 
 			cmd = c;
 			n = out[0].rm_eo - out[0].rm_so;
 			cmd_arg = xmemdupz(dir + out[0].rm_so + 1, n - 1);
 			dir[out[0].rm_so] = 0;
 			break;
 		}
 		regfree(&re);
 	}
 
 	if (!cmd)
-		not_found("Request not supported: '%s'", dir);
+		not_found(&hdr, "Request not supported: '%s'", dir);
 
 	setup_path();
 	if (!enter_repo(dir, 0))
-		not_found("Not a git repository: '%s'", dir);
+		not_found(&hdr, "Not a git repository: '%s'", dir);
 	if (!getenv("GIT_HTTP_EXPORT_ALL") &&
 	    access("git-daemon-export-ok", F_OK) )
-		not_found("Repository not exported: '%s'", dir);
+		not_found(&hdr, "Repository not exported: '%s'", dir);
 
 	http_config();
 	max_request_buffer = git_env_ulong("GIT_HTTP_MAX_REQUEST_BUFFER",
 					   max_request_buffer);
 
-	cmd->imp(cmd_arg);
+	cmd->imp(&hdr, cmd_arg);
 	return 0;
 }
