 };
 
 static int check_symref(const char *HEAD, int quiet, int shorten, int print)
 {
 	unsigned char sha1[20];
 	int flag;
-	const char *refname = resolve_ref_unsafe(HEAD, sha1, 0, &flag);
+	const char *refname = resolve_ref_unsafe(HEAD, 0, sha1, &flag);
 
 	if (!refname)
 		die("No such ref: %s", HEAD);
 	else if (!(flag & REF_ISSYMREF)) {
 		if (!quiet)
 			die("ref %s is not a symbolic ref", HEAD);
