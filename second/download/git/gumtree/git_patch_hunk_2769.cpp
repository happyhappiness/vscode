  *
  * Returns 1 if the patch should be skipped, 0 otherwise.
  */
 static int parse_mail(struct am_state *state, const char *mail)
 {
 	FILE *fp;
-	struct child_process cp = CHILD_PROCESS_INIT;
 	struct strbuf sb = STRBUF_INIT;
 	struct strbuf msg = STRBUF_INIT;
 	struct strbuf author_name = STRBUF_INIT;
 	struct strbuf author_date = STRBUF_INIT;
 	struct strbuf author_email = STRBUF_INIT;
 	int ret = 0;
+	struct mailinfo mi;
 
-	cp.git_cmd = 1;
-	cp.in = xopen(mail, O_RDONLY, 0);
-	cp.out = xopen(am_path(state, "info"), O_WRONLY | O_CREAT, 0777);
+	setup_mailinfo(&mi);
 
-	argv_array_push(&cp.args, "mailinfo");
-	argv_array_push(&cp.args, state->utf8 ? "-u" : "-n");
+	if (state->utf8)
+		mi.metainfo_charset = get_commit_output_encoding();
+	else
+		mi.metainfo_charset = NULL;
 
 	switch (state->keep) {
 	case KEEP_FALSE:
 		break;
 	case KEEP_TRUE:
-		argv_array_push(&cp.args, "-k");
+		mi.keep_subject = 1;
 		break;
 	case KEEP_NON_PATCH:
-		argv_array_push(&cp.args, "-b");
+		mi.keep_non_patch_brackets_in_subject = 1;
 		break;
 	default:
 		die("BUG: invalid value for state->keep");
 	}
 
 	if (state->message_id)
-		argv_array_push(&cp.args, "-m");
+		mi.add_message_id = 1;
 
 	switch (state->scissors) {
 	case SCISSORS_UNSET:
 		break;
 	case SCISSORS_FALSE:
-		argv_array_push(&cp.args, "--no-scissors");
+		mi.use_scissors = 0;
 		break;
 	case SCISSORS_TRUE:
-		argv_array_push(&cp.args, "--scissors");
+		mi.use_scissors = 1;
 		break;
 	default:
 		die("BUG: invalid value for state->scissors");
 	}
 
-	argv_array_push(&cp.args, am_path(state, "msg"));
-	argv_array_push(&cp.args, am_path(state, "patch"));
-
-	if (run_command(&cp) < 0)
+	mi.input = fopen(mail, "r");
+	if (!mi.input)
+		die("could not open input");
+	mi.output = fopen(am_path(state, "info"), "w");
+	if (!mi.output)
+		die("could not open output 'info'");
+	if (mailinfo(&mi, am_path(state, "msg"), am_path(state, "patch")))
 		die("could not parse patch");
 
-	close(cp.in);
-	close(cp.out);
+	fclose(mi.input);
+	fclose(mi.output);
 
 	/* Extract message and author information */
 	fp = xfopen(am_path(state, "info"), "r");
 	while (!strbuf_getline(&sb, fp, '\n')) {
 		const char *x;
 
