 	}
 	return 0;
 }
 
 int check_filename(const char *prefix, const char *arg)
 {
-	const char *name;
 	char *to_free = NULL;
 	struct stat st;
 
-	if (starts_with(arg, ":/")) {
-		if (arg[2] == '\0') /* ":/" is root dir, always exists */
+	if (skip_prefix(arg, ":/", &arg)) {
+		if (!*arg) /* ":/" is root dir, always exists */
 			return 1;
-		name = arg + 2;
-	} else if (prefix)
-		name = to_free = prefix_filename(prefix, arg);
-	else
-		name = arg;
-	if (!lstat(name, &st)) {
+		prefix = NULL;
+	} else if (skip_prefix(arg, ":!", &arg) ||
+		   skip_prefix(arg, ":^", &arg)) {
+		if (!*arg) /* excluding everything is silly, but allowed */
+			return 1;
+	}
+
+	if (prefix)
+		arg = to_free = prefix_filename(prefix, arg);
+
+	if (!lstat(arg, &st)) {
 		free(to_free);
 		return 1; /* file exists */
 	}
-	if (errno == ENOENT || errno == ENOTDIR) {
+	if (is_missing_file_error(errno)) {
 		free(to_free);
 		return 0; /* file does not exist */
 	}
 	die_errno("failed to stat '%s'", arg);
 }
 
