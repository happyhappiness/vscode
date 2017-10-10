 	commit_list_insert(commit, opt->value);
 	return 0;
 }
 
 int parse_opt_object_name(const struct option *opt, const char *arg, int unset)
 {
-	unsigned char sha1[20];
+	struct object_id oid;
 
 	if (unset) {
-		sha1_array_clear(opt->value);
+		oid_array_clear(opt->value);
 		return 0;
 	}
 	if (!arg)
 		return -1;
-	if (get_sha1(arg, sha1))
+	if (get_oid(arg, &oid))
 		return error(_("malformed object name '%s'"), arg);
-	sha1_array_append(opt->value, sha1);
+	oid_array_append(opt->value, &oid);
 	return 0;
 }
 
 int parse_opt_tertiary(const struct option *opt, const char *arg, int unset)
 {
 	int *target = opt->value;
