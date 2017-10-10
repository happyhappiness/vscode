 
 static int add_ref_decoration(const char *refname, const unsigned char *sha1, int flags, void *cb_data)
 {
 	struct object *obj;
 	enum decoration_type type = DECORATION_NONE;
 
+	assert(cb_data == NULL);
+
 	if (starts_with(refname, "refs/replace/")) {
 		unsigned char original_sha1[20];
 		if (!check_replace_refs)
 			return 0;
 		if (get_sha1_hex(refname + 13, original_sha1)) {
 			warning("invalid replace ref %s", refname);
