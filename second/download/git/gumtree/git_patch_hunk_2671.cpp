 }
 
 static void print_commit(struct commit *commit)
 {
 	struct strbuf sb = STRBUF_INIT;
 	struct pretty_print_context ctx = {0};
-	ctx.date_mode = DATE_NORMAL;
+	ctx.date_mode.type = DATE_NORMAL;
 	format_commit_message(commit, " %h: %m %s", &sb, &ctx);
 	fprintf(stderr, "%s\n", sb.buf);
 	strbuf_release(&sb);
 }
 
 #define MERGE_WARNING(path, msg) \
