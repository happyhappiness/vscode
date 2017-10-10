 		    git_committer_info(IDENT_NO_NAME|IDENT_NO_DATE|IDENT_STRICT));
 	info->message_id = strbuf_detach(&buf, NULL);
 }
 
 static void print_signature(void)
 {
-	if (signature && *signature)
-		printf("-- \n%s\n\n", signature);
+	if (!signature || !*signature)
+		return;
+
+	printf("-- \n%s", signature);
+	if (signature[strlen(signature)-1] != '\n')
+		putchar('\n');
+	putchar('\n');
 }
 
 static void add_branch_description(struct strbuf *buf, const char *branch_name)
 {
 	struct strbuf desc = STRBUF_INIT;
 	if (!branch_name || !*branch_name)
 		return;
 	read_branch_desc(&desc, branch_name);
 	if (desc.len) {
 		strbuf_addch(buf, '\n');
-		strbuf_add(buf, desc.buf, desc.len);
+		strbuf_addbuf(buf, &desc);
 		strbuf_addch(buf, '\n');
 	}
 }
 
 static char *find_branch_name(struct rev_info *rev)
 {
 	int i, positive = -1;
 	unsigned char branch_sha1[20];
 	const unsigned char *tip_sha1;
-	const char *ref;
+	const char *ref, *v;
 	char *full_ref, *branch = NULL;
 
 	for (i = 0; i < rev->cmdline.nr; i++) {
 		if (rev->cmdline.rev[i].flags & UNINTERESTING)
 			continue;
 		if (positive < 0)
