 	strbuf_addf(&buf, "%s.%lu.git.%s", base,
 		    (unsigned long) time(NULL),
 		    git_committer_info(IDENT_NO_NAME|IDENT_NO_DATE|IDENT_STRICT));
 	info->message_id = strbuf_detach(&buf, NULL);
 }
 
-static void print_signature(void)
+static void print_signature(FILE *file)
 {
 	if (!signature || !*signature)
 		return;
 
-	printf("-- \n%s", signature);
+	fprintf(file, "-- \n%s", signature);
 	if (signature[strlen(signature)-1] != '\n')
-		putchar('\n');
-	putchar('\n');
+		putc('\n', file);
+	putc('\n', file);
 }
 
 static void add_branch_description(struct strbuf *buf, const char *branch_name)
 {
 	struct strbuf desc = STRBUF_INIT;
 	if (!branch_name || !*branch_name)
