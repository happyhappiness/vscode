 
 static void create_tag(const unsigned char *object, const char *tag,
 		       struct strbuf *buf, struct create_tag_options *opt,
 		       unsigned char *prev, unsigned char *result)
 {
 	enum object_type type;
-	char header_buf[1024];
-	int header_len;
+	struct strbuf header = STRBUF_INIT;
 	char *path = NULL;
 
 	type = sha1_object_info(object, NULL);
 	if (type <= OBJ_NONE)
 	    die(_("bad object type."));
 
-	header_len = snprintf(header_buf, sizeof(header_buf),
-			  "object %s\n"
-			  "type %s\n"
-			  "tag %s\n"
-			  "tagger %s\n\n",
-			  sha1_to_hex(object),
-			  typename(type),
-			  tag,
-			  git_committer_info(IDENT_STRICT));
-
-	if (header_len > sizeof(header_buf) - 1)
-		die(_("tag header too big."));
+	strbuf_addf(&header,
+		    "object %s\n"
+		    "type %s\n"
+		    "tag %s\n"
+		    "tagger %s\n\n",
+		    sha1_to_hex(object),
+		    typename(type),
+		    tag,
+		    git_committer_info(IDENT_STRICT));
 
 	if (!opt->message_given) {
 		int fd;
 
 		/* write the template message before editing: */
 		path = git_pathdup("TAG_EDITMSG");
