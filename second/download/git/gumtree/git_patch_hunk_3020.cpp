  * This creates a temporary file in the same directory as the final
  * 'filename'
  *
  * We want to avoid cross-directory filename renames, because those
  * can have problems on various filesystems (FAT, NFS, Coda).
  */
-static int create_tmpfile(char *buffer, size_t bufsiz, const char *filename)
+static int create_tmpfile(struct strbuf *tmp, const char *filename)
 {
 	int fd, dirlen = directory_size(filename);
 
-	if (dirlen + 20 > bufsiz) {
-		errno = ENAMETOOLONG;
-		return -1;
-	}
-	memcpy(buffer, filename, dirlen);
-	strcpy(buffer + dirlen, "tmp_obj_XXXXXX");
-	fd = git_mkstemp_mode(buffer, 0444);
+	strbuf_reset(tmp);
+	strbuf_add(tmp, filename, dirlen);
+	strbuf_addstr(tmp, "tmp_obj_XXXXXX");
+	fd = git_mkstemp_mode(tmp->buf, 0444);
 	if (fd < 0 && dirlen && errno == ENOENT) {
-		/* Make sure the directory exists */
-		memcpy(buffer, filename, dirlen);
-		buffer[dirlen-1] = 0;
-		if (mkdir(buffer, 0777) && errno != EEXIST)
+		/*
+		 * Make sure the directory exists; note that the contents
+		 * of the buffer are undefined after mkstemp returns an
+		 * error, so we have to rewrite the whole buffer from
+		 * scratch.
+		 */
+		strbuf_reset(tmp);
+		strbuf_add(tmp, filename, dirlen - 1);
+		if (mkdir(tmp->buf, 0777) && errno != EEXIST)
 			return -1;
-		if (adjust_shared_perm(buffer))
+		if (adjust_shared_perm(tmp->buf))
 			return -1;
 
 		/* Try again */
-		strcpy(buffer + dirlen - 1, "/tmp_obj_XXXXXX");
-		fd = git_mkstemp_mode(buffer, 0444);
+		strbuf_addstr(tmp, "/tmp_obj_XXXXXX");
+		fd = git_mkstemp_mode(tmp->buf, 0444);
 	}
 	return fd;
 }
 
 static int write_loose_object(const unsigned char *sha1, char *hdr, int hdrlen,
 			      const void *buf, unsigned long len, time_t mtime)
 {
 	int fd, ret;
 	unsigned char compressed[4096];
 	git_zstream stream;
 	git_SHA_CTX c;
 	unsigned char parano_sha1[20];
-	static char tmp_file[PATH_MAX];
+	static struct strbuf tmp_file = STRBUF_INIT;
 	const char *filename = sha1_file_name(sha1);
 
-	fd = create_tmpfile(tmp_file, sizeof(tmp_file), filename);
+	fd = create_tmpfile(&tmp_file, filename);
 	if (fd < 0) {
 		if (errno == EACCES)
 			return error("insufficient permission for adding an object to repository database %s", get_object_directory());
 		else
 			return error("unable to create temporary file: %s", strerror(errno));
 	}
