 
 static const char commit_utf8_warn[] =
 "Warning: commit message did not conform to UTF-8.\n"
 "You may want to amend it after fixing the message, or set the config\n"
 "variable i18n.commitencoding to the encoding your project uses.\n";
 
-int commit_tree_extended(const struct strbuf *msg, const unsigned char *tree,
+int commit_tree_extended(const char *msg, size_t msg_len,
+			 const unsigned char *tree,
 			 struct commit_list *parents, unsigned char *ret,
 			 const char *author, const char *sign_commit,
 			 struct commit_extra_header *extra)
 {
 	int result;
 	int encoding_is_utf8;
 	struct strbuf buffer;
 
 	assert_sha1_type(tree, OBJ_TREE);
 
-	if (memchr(msg->buf, '\0', msg->len))
+	if (memchr(msg, '\0', msg_len))
 		return error("a NUL byte in commit log message not allowed.");
 
 	/* Not having i18n.commitencoding is the same as having utf-8 */
 	encoding_is_utf8 = is_encoding_utf8(git_commit_encoding);
 
 	strbuf_init(&buffer, 8192); /* should avoid reallocs for the headers */
