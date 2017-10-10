 		"git bisect cannot work properly in this case.\n"
 		"Maybe you mistook %s and %s revs?\n"),
 		term_good, term_bad, term_good, term_bad);
 	exit(1);
 }
 
-static void handle_skipped_merge_base(const unsigned char *mb)
+static void handle_skipped_merge_base(const struct object_id *mb)
 {
-	char *mb_hex = sha1_to_hex(mb);
+	char *mb_hex = oid_to_hex(mb);
 	char *bad_hex = oid_to_hex(current_bad_oid);
 	char *good_hex = join_sha1_array_hex(&good_revs, ' ');
 
 	warning(_("the merge base between %s and [%s] "
 		"must be skipped.\n"
 		"So we cannot be sure the first %s commit is "
