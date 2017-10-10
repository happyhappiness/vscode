 	if (!default_refs) {
 		fprintf(stderr, "notice: No default references\n");
 		show_unreachable = 0;
 	}
 }
 
+static int fsck_loose(const unsigned char *sha1, const char *path, void *data)
+{
+	if (fsck_sha1(sha1))
+		errors_found |= ERROR_OBJECT;
+	return 0;
+}
+
+static int fsck_cruft(const char *basename, const char *path, void *data)
+{
+	if (!starts_with(basename, "tmp_obj_"))
+		fprintf(stderr, "bad sha1 file: %s\n", path);
+	return 0;
+}
+
+static int fsck_subdir(int nr, const char *path, void *progress)
+{
+	display_progress(progress, nr + 1);
+	return 0;
+}
+
 static void fsck_object_dir(const char *path)
 {
-	int i;
 	struct progress *progress = NULL;
 
 	if (verbose)
 		fprintf(stderr, "Checking object directory\n");
 
 	if (show_progress)
 		progress = start_progress(_("Checking object directories"), 256);
-	for (i = 0; i < 256; i++) {
-		static char dir[4096];
-		sprintf(dir, "%s/%02x", path, i);
-		fsck_dir(i, dir);
-		display_progress(progress, i+1);
-	}
+
+	for_each_loose_file_in_objdir(path, fsck_loose, fsck_cruft, fsck_subdir,
+				      progress);
+	display_progress(progress, 256);
 	stop_progress(&progress);
-	fsck_sha1_list();
 }
 
 static int fsck_head_link(void)
 {
 	int flag;
 	int null_is_error = 0;
