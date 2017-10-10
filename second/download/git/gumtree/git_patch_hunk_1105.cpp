 		struct child_process cp = CHILD_PROCESS_INIT;
 		struct strbuf sb = STRBUF_INIT;
 
 		if (flags & ~ABSORB_GITDIR_RECURSE_SUBMODULES)
 			die("BUG: we don't know how to pass the flags down?");
 
-		if (get_super_prefix())
-			strbuf_addstr(&sb, get_super_prefix());
+		strbuf_addstr(&sb, get_super_prefix_or_empty());
 		strbuf_addstr(&sb, path);
 		strbuf_addch(&sb, '/');
 
 		cp.dir = path;
 		cp.git_cmd = 1;
 		cp.no_stdin = 1;
