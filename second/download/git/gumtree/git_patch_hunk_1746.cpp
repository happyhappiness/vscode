 	N_("git prune-packed [-n|--dry-run] [-q|--quiet]"),
 	NULL
 };
 
 static struct progress *progress;
 
-static void prune_dir(int i, DIR *dir, struct strbuf *pathname, int opts)
+static int prune_subdir(int nr, const char *path, void *data)
 {
-	struct dirent *de;
-	char hex[40];
-	int top_len = pathname->len;
-
-	sprintf(hex, "%02x", i);
-	while ((de = readdir(dir)) != NULL) {
-		unsigned char sha1[20];
-		if (strlen(de->d_name) != 38)
-			continue;
-		memcpy(hex + 2, de->d_name, 38);
-		if (get_sha1_hex(hex, sha1))
-			continue;
-		if (!has_sha1_pack(sha1))
-			continue;
-
-		strbuf_add(pathname, de->d_name, 38);
-		if (opts & PRUNE_PACKED_DRY_RUN)
-			printf("rm -f %s\n", pathname->buf);
-		else
-			unlink_or_warn(pathname->buf);
-		display_progress(progress, i + 1);
-		strbuf_setlen(pathname, top_len);
-	}
+	int *opts = data;
+	display_progress(progress, nr + 1);
+	if (!(*opts & PRUNE_PACKED_DRY_RUN))
+		rmdir(path);
+	return 0;
 }
 
-void prune_packed_objects(int opts)
+static int prune_object(const unsigned char *sha1, const char *path,
+			 void *data)
 {
-	int i;
-	const char *dir = get_object_directory();
-	struct strbuf pathname = STRBUF_INIT;
-	int top_len;
+	int *opts = data;
+
+	if (!has_sha1_pack(sha1))
+		return 0;
+
+	if (*opts & PRUNE_PACKED_DRY_RUN)
+		printf("rm -f %s\n", path);
+	else
+		unlink_or_warn(path);
+	return 0;
+}
 
-	strbuf_addstr(&pathname, dir);
+void prune_packed_objects(int opts)
+{
 	if (opts & PRUNE_PACKED_VERBOSE)
 		progress = start_progress_delay(_("Removing duplicate objects"),
 			256, 95, 2);
 
-	if (pathname.len && pathname.buf[pathname.len - 1] != '/')
-		strbuf_addch(&pathname, '/');
+	for_each_loose_file_in_objdir(get_object_directory(),
+				      prune_object, NULL, prune_subdir, &opts);
 
-	top_len = pathname.len;
-	for (i = 0; i < 256; i++) {
-		DIR *d;
-
-		display_progress(progress, i + 1);
-		strbuf_setlen(&pathname, top_len);
-		strbuf_addf(&pathname, "%02x/", i);
-		d = opendir(pathname.buf);
-		if (!d)
-			continue;
-		prune_dir(i, d, &pathname, opts);
-		closedir(d);
-		strbuf_setlen(&pathname, top_len + 2);
-		rmdir(pathname.buf);
-	}
+	/* Ensure we show 100% before finishing progress */
+	display_progress(progress, 256);
 	stop_progress(&progress);
 }
 
 int cmd_prune_packed(int argc, const char **argv, const char *prefix)
 {
 	int opts = isatty(2) ? PRUNE_PACKED_VERBOSE : 0;
