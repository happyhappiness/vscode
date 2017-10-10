 static int grab_single_ref(const char *refname, const unsigned char *sha1, int flag, void *cb_data)
 {
 	struct grab_ref_cbdata *cb = cb_data;
 	struct refinfo *ref;
 	int cnt;
 
+	if (flag & REF_BAD_NAME) {
+		  warning("ignoring ref with broken name %s", refname);
+		  return 0;
+	}
+
 	if (*cb->grab_pattern) {
 		const char **pattern;
 		int namelen = strlen(refname);
 		for (pattern = cb->grab_pattern; *pattern; pattern++) {
 			const char *p = *pattern;
 			int plen = strlen(p);
