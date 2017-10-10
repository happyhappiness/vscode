 	if (kind == OBJ_TREE || kind == OBJ_COMMIT)
 		return 1;
 	if (kind != OBJ_TAG)
 		return 0;
 
 	/* We need to do this the hard way... */
-	obj = deref_tag(lookup_object(sha1), NULL, 0);
+	obj = deref_tag(parse_object(sha1), NULL, 0);
 	if (obj && (obj->type == OBJ_TREE || obj->type == OBJ_COMMIT))
 		return 1;
 	return 0;
 }
 
 static int disambiguate_blob_only(const unsigned char *sha1, void *cb_data_unused)
 {
 	int kind = sha1_object_info(sha1, NULL);
 	return kind == OBJ_BLOB;
 }
 
-static int prepare_prefixes(const char *name, int len,
-			    unsigned char *bin_pfx,
-			    char *hex_pfx)
+static disambiguate_hint_fn default_disambiguate_hint;
+
+int set_disambiguate_hint_config(const char *var, const char *value)
 {
+	static const struct {
+		const char *name;
+		disambiguate_hint_fn fn;
+	} hints[] = {
+		{ "none", NULL },
+		{ "commit", disambiguate_commit_only },
+		{ "committish", disambiguate_committish_only },
+		{ "tree", disambiguate_tree_only },
+		{ "treeish", disambiguate_treeish_only },
+		{ "blob", disambiguate_blob_only }
+	};
 	int i;
 
-	hashclr(bin_pfx);
-	memset(hex_pfx, 'x', 40);
+	if (!value)
+		return config_error_nonbool(var);
+
+	for (i = 0; i < ARRAY_SIZE(hints); i++) {
+		if (!strcasecmp(value, hints[i].name)) {
+			default_disambiguate_hint = hints[i].fn;
+			return 0;
+		}
+	}
+
+	return error("unknown hint type for '%s': %s", var, value);
+}
+
+static int init_object_disambiguation(const char *name, int len,
+				      struct disambiguate_state *ds)
+{
+	int i;
+
+	if (len < MINIMUM_ABBREV || len > GIT_SHA1_HEXSZ)
+		return -1;
+
+	memset(ds, 0, sizeof(*ds));
+
 	for (i = 0; i < len ;i++) {
 		unsigned char c = name[i];
 		unsigned char val;
 		if (c >= '0' && c <= '9')
 			val = c - '0';
 		else if (c >= 'a' && c <= 'f')
