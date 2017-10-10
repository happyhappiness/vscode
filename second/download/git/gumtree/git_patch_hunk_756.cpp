 	}
 	git_SHA1_Final(real_sha1, &c);
 	close_istream(st);
 	return hashcmp(sha1, real_sha1) ? -1 : 0;
 }
 
-int git_open(const char *name)
+int git_open_cloexec(const char *name, int flags)
 {
-	static int sha1_file_open_flag = O_NOATIME | O_CLOEXEC;
-
-	for (;;) {
-		int fd;
-
-		errno = 0;
-		fd = open(name, O_RDONLY | sha1_file_open_flag);
-		if (fd >= 0)
-			return fd;
+	int fd;
+	static int o_cloexec = O_CLOEXEC;
 
+	fd = open(name, flags | o_cloexec);
+	if ((o_cloexec & O_CLOEXEC) && fd < 0 && errno == EINVAL) {
 		/* Try again w/o O_CLOEXEC: the kernel might not support it */
-		if ((sha1_file_open_flag & O_CLOEXEC) && errno == EINVAL) {
-			sha1_file_open_flag &= ~O_CLOEXEC;
-			continue;
-		}
+		o_cloexec &= ~O_CLOEXEC;
+		fd = open(name, flags | o_cloexec);
+	}
 
-		/* Might the failure be due to O_NOATIME? */
-		if (errno != ENOENT && (sha1_file_open_flag & O_NOATIME)) {
-			sha1_file_open_flag &= ~O_NOATIME;
-			continue;
+#if defined(F_GETFL) && defined(F_SETFL) && defined(FD_CLOEXEC)
+	{
+		static int fd_cloexec = FD_CLOEXEC;
+
+		if (!o_cloexec && 0 <= fd && fd_cloexec) {
+			/* Opened w/o O_CLOEXEC?  try with fcntl(2) to add it */
+			int flags = fcntl(fd, F_GETFL);
+			if (fcntl(fd, F_SETFL, flags | fd_cloexec))
+				fd_cloexec = 0;
 		}
-		return -1;
 	}
+#endif
+	return fd;
 }
 
-static int stat_sha1_file(const unsigned char *sha1, struct stat *st)
+/*
+ * Find "sha1" as a loose object in the local repository or in an alternate.
+ * Returns 0 on success, negative on failure.
+ *
+ * The "path" out-parameter will give the path of the object we found (if any).
+ * Note that it may point to static storage and is only valid until another
+ * call to sha1_file_name(), etc.
+ */
+static int stat_sha1_file(const unsigned char *sha1, struct stat *st,
+			  const char **path)
 {
 	struct alternate_object_database *alt;
 
-	if (!lstat(sha1_file_name(sha1), st))
+	*path = sha1_file_name(sha1);
+	if (!lstat(*path, st))
 		return 0;
 
 	prepare_alt_odb();
 	errno = ENOENT;
 	for (alt = alt_odb_list; alt; alt = alt->next) {
-		const char *path = alt_sha1_path(alt, sha1);
-		if (!lstat(path, st))
+		*path = alt_sha1_path(alt, sha1);
+		if (!lstat(*path, st))
 			return 0;
 	}
 
 	return -1;
 }
 
-static int open_sha1_file(const unsigned char *sha1)
+/*
+ * Like stat_sha1_file(), but actually open the object and return the
+ * descriptor. See the caveats on the "path" parameter above.
+ */
+static int open_sha1_file(const unsigned char *sha1, const char **path)
 {
 	int fd;
 	struct alternate_object_database *alt;
 	int most_interesting_errno;
 
-	fd = git_open(sha1_file_name(sha1));
+	*path = sha1_file_name(sha1);
+	fd = git_open(*path);
 	if (fd >= 0)
 		return fd;
 	most_interesting_errno = errno;
 
 	prepare_alt_odb();
 	for (alt = alt_odb_list; alt; alt = alt->next) {
-		const char *path = alt_sha1_path(alt, sha1);
-		fd = git_open(path);
+		*path = alt_sha1_path(alt, sha1);
+		fd = git_open(*path);
 		if (fd >= 0)
 			return fd;
 		if (most_interesting_errno == ENOENT)
 			most_interesting_errno = errno;
 	}
 	errno = most_interesting_errno;
 	return -1;
 }
 
-void *map_sha1_file(const unsigned char *sha1, unsigned long *size)
+/*
+ * Map the loose object at "path" if it is not NULL, or the path found by
+ * searching for a loose object named "sha1".
+ */
+static void *map_sha1_file_1(const char *path,
+			     const unsigned char *sha1,
+			     unsigned long *size)
 {
 	void *map;
 	int fd;
 
-	fd = open_sha1_file(sha1);
+	if (path)
+		fd = git_open(path);
+	else
+		fd = open_sha1_file(sha1, &path);
 	map = NULL;
 	if (fd >= 0) {
 		struct stat st;
 
 		if (!fstat(fd, &st)) {
 			*size = xsize_t(st.st_size);
 			if (!*size) {
 				/* mmap() is forbidden on empty files */
-				error("object file %s is empty", sha1_file_name(sha1));
+				error("object file %s is empty", path);
 				return NULL;
 			}
 			map = xmmap(NULL, *size, PROT_READ, MAP_PRIVATE, fd, 0);
 		}
 		close(fd);
 	}
 	return map;
 }
 
+void *map_sha1_file(const unsigned char *sha1, unsigned long *size)
+{
+	return map_sha1_file_1(NULL, sha1, size);
+}
+
 unsigned long unpack_object_header_buffer(const unsigned char *buf,
 		unsigned long len, enum object_type *type, unsigned long *sizep)
 {
 	unsigned shift;
 	unsigned long size, c;
 	unsigned long used = 0;
