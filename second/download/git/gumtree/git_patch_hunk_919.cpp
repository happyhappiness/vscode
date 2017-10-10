  * Is there one among the list of patterns that match the tail part
  * of the path?
  */
 static int tail_match(const char **pattern, const char *path)
 {
 	const char *p;
-	char pathbuf[PATH_MAX];
+	char *pathbuf;
 
 	if (!pattern)
 		return 1; /* no restriction */
 
-	if (snprintf(pathbuf, sizeof(pathbuf), "/%s", path) > sizeof(pathbuf))
-		return error("insanely long ref %.*s...", 20, path);
+	pathbuf = xstrfmt("/%s", path);
 	while ((p = *(pattern++)) != NULL) {
-		if (!wildmatch(p, pathbuf, 0, NULL))
+		if (!wildmatch(p, pathbuf, 0, NULL)) {
+			free(pathbuf);
 			return 1;
+		}
 	}
+	free(pathbuf);
 	return 0;
 }
 
 int cmd_ls_remote(int argc, const char **argv, const char *prefix)
 {
 	const char *dest = NULL;
