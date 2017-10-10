 		printf("%s\n", find_unique_abbrev(sha1, DEFAULT_ABBREV));
 	else
 		die("cannot describe '%s'", sha1_to_hex(sha1));
 }
 
 static char const * const name_rev_usage[] = {
-	N_("git name-rev [options] <commit>..."),
-	N_("git name-rev [options] --all"),
-	N_("git name-rev [options] --stdin"),
+	N_("git name-rev [<options>] <commit>..."),
+	N_("git name-rev [<options>] --all"),
+	N_("git name-rev [<options>] --stdin"),
 	NULL
 };
 
 static void name_rev_line(char *p, struct name_ref_data *data)
 {
 	int forty = 0;
