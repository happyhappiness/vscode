 	cp.argv = argv;
 	cp.env = local_repo_env;
 	cp.no_stdin = 1;
 	cp.use_shell = 1;
 
 	if (capture_command(&cp, &buf, 1024)) {
-		error("running trailer command '%s' failed", cmd.buf);
+		error(_("running trailer command '%s' failed"), cmd.buf);
 		strbuf_release(&buf);
 		result = xstrdup("");
 	} else {
 		strbuf_trim(&buf);
 		result = strbuf_detach(&buf, NULL);
 	}
