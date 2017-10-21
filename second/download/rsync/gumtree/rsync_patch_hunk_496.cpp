 	while (*s1 && *s2 && (*s1 == *s2)) {
 		s1++; s2++;
 	}
 	
 	return (int)*s1 - (int)*s2;
 }
+
+static OFF_T last_ofs;
+
+void end_progress(void)
+{
+	extern int do_progress, am_server;
+
+	if (do_progress && !am_server) {
+		rprintf(FINFO,"\n");
+	}
+	last_ofs = 0;
+}
+
+void show_progress(OFF_T ofs, OFF_T size)
+{
+	extern int do_progress, am_server;
+
+	if (do_progress && !am_server) {
+		if (ofs > last_ofs + 1000) {
+			int pct = (int)((100.0*ofs)/size);
+			rprintf(FINFO,"%.0f (%d%%)\r", (double)ofs, pct);
+			last_ofs = ofs;
+		}
+	}
+}
+
+/* determine if a symlink points outside the current directory tree */
+int unsafe_symlink(char *dest, char *src)
+{
+	char *tok;
+	int depth = 0;
+
+	/* all absolute and null symlinks are unsafe */
+	if (!dest || !(*dest) || (*dest == '/')) return 1;
+
+	src = strdup(src);
+	if (!src) out_of_memory("unsafe_symlink");
+
+	/* find out what our safety margin is */
+	for (tok=strtok(src,"/"); tok; tok=strtok(NULL,"/")) {
+		if (strcmp(tok,"..") == 0) {
+			depth=0;
+		} else if (strcmp(tok,".") == 0) {
+			/* nothing */
+		} else {
+			depth++;
+		}
+	}
+	free(src);
+
+	/* drop by one to account for the filename portion */
+	depth--;
+
+	dest = strdup(dest);
+	if (!dest) out_of_memory("unsafe_symlink");
+
+	for (tok=strtok(dest,"/"); tok; tok=strtok(NULL,"/")) {
+		if (strcmp(tok,"..") == 0) {
+			depth--;
+		} else if (strcmp(tok,".") == 0) {
+			/* nothing */
+		} else {
+			depth++;
+		}
+		/* if at any point we go outside the current directory then
+		   stop - it is unsafe */
+		if (depth < 0) break;
+	}
+
+	free(dest);
+	return (depth < 0);
+}
