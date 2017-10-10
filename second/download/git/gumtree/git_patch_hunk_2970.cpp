 	if (((old_mode ^ new_mode) & ~S_IFMT) &&
 			chmod(path, (new_mode & ~S_IFMT)) < 0)
 		return -2;
 	return 0;
 }
 
+void safe_create_dir(const char *dir, int share)
+{
+	if (mkdir(dir, 0777) < 0) {
+		if (errno != EEXIST) {
+			perror(dir);
+			exit(1);
+		}
+	}
+	else if (share && adjust_shared_perm(dir))
+		die(_("Could not make %s writable by group"), dir);
+}
+
 static int have_same_root(const char *path1, const char *path2)
 {
 	int is_abs1, is_abs2;
 
 	is_abs1 = is_absolute_path(path1);
 	is_abs2 = is_absolute_path(path2);
