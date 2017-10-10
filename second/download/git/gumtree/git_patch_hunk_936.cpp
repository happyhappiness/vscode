 static int err;
 
 static int merge_entry(int pos, const char *path)
 {
 	int found;
 	const char *arguments[] = { pgm, "", "", "", path, "", "", "", NULL };
-	char hexbuf[4][GIT_SHA1_HEXSZ + 1];
+	char hexbuf[4][GIT_MAX_HEXSZ + 1];
 	char ownbuf[4][60];
 
 	if (pos >= active_nr)
 		die("git merge-index: %s not in the cache", path);
 	found = 0;
 	do {
