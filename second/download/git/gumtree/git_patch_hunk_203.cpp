 }
 
 int try_merge_command(const char *strategy, size_t xopts_nr,
 		      const char **xopts, struct commit_list *common,
 		      const char *head_arg, struct commit_list *remotes)
 {
-	const char **args;
-	int i = 0, x = 0, ret;
+	struct argv_array args = ARGV_ARRAY_INIT;
+	int i, ret;
 	struct commit_list *j;
-	struct strbuf buf = STRBUF_INIT;
 
-	args = xmalloc((4 + xopts_nr + commit_list_count(common) +
-			commit_list_count(remotes)) * sizeof(char *));
-	strbuf_addf(&buf, "merge-%s", strategy);
-	args[i++] = buf.buf;
-	for (x = 0; x < xopts_nr; x++) {
-		char *s = xmalloc(strlen(xopts[x])+2+1);
-		strcpy(s, "--");
-		strcpy(s+2, xopts[x]);
-		args[i++] = s;
-	}
-	for (j = common; j; j = j->next)
-		args[i++] = xstrdup(merge_argument(j->item));
-	args[i++] = "--";
-	args[i++] = head_arg;
-	for (j = remotes; j; j = j->next)
-		args[i++] = xstrdup(merge_argument(j->item));
-	args[i] = NULL;
-	ret = run_command_v_opt(args, RUN_GIT_CMD);
-	strbuf_release(&buf);
-	i = 1;
-	for (x = 0; x < xopts_nr; x++)
-		free((void *)args[i++]);
+	argv_array_pushf(&args, "merge-%s", strategy);
+	for (i = 0; i < xopts_nr; i++)
+		argv_array_pushf(&args, "--%s", xopts[i]);
 	for (j = common; j; j = j->next)
-		free((void *)args[i++]);
-	i += 2;
+		argv_array_push(&args, merge_argument(j->item));
+	argv_array_push(&args, "--");
+	argv_array_push(&args, head_arg);
 	for (j = remotes; j; j = j->next)
-		free((void *)args[i++]);
-	free(args);
+		argv_array_push(&args, merge_argument(j->item));
+
+	ret = run_command_v_opt(args.argv, RUN_GIT_CMD);
+	argv_array_clear(&args);
+
 	discard_cache();
 	if (read_cache() < 0)
 		die(_("failed to read the cache"));
 	resolve_undo_clear();
 
 	return ret;
