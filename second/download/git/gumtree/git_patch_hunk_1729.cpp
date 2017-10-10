 	unlink(git_path("MERGE_MODE"));
 }
 
 static int save_state(unsigned char *stash)
 {
 	int len;
-	struct child_process cp;
+	struct child_process cp = CHILD_PROCESS_INIT;
 	struct strbuf buffer = STRBUF_INIT;
 	const char *argv[] = {"stash", "create", NULL};
 
-	memset(&cp, 0, sizeof(cp));
 	cp.argv = argv;
 	cp.out = -1;
 	cp.git_cmd = 1;
 
 	if (start_command(&cp))
 		die(_("could not run stash."));
