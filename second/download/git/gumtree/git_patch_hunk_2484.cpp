 {
 	char *filename = git_pathdup("BISECT_ANCESTORS_OK");
 	struct stat st;
 	int fd;
 
 	if (!current_bad_oid)
-		die("a bad revision is needed");
+		die("a %s revision is needed", term_bad);
 
 	/* Check if file BISECT_ANCESTORS_OK exists. */
 	if (!stat(filename, &st) && S_ISREG(st.st_mode))
 		goto done;
 
 	/* Bisecting with no good rev is ok. */
