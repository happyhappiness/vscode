 		del = total - add;
 	}
 	printf("%5d %.*s%.*s\n", patch->lines_added + patch->lines_deleted,
 		add, pluses, del, minuses);
 }
 
-static int read_old_data(struct stat *st, const char *path, struct strbuf *buf)
+static int read_old_data(struct stat *st, struct patch *patch,
+			 const char *path, struct strbuf *buf)
 {
+	enum safe_crlf safe_crlf = patch->crlf_in_old ?
+		SAFE_CRLF_KEEP_CRLF : SAFE_CRLF_RENORMALIZE;
 	switch (st->st_mode & S_IFMT) {
 	case S_IFLNK:
 		if (strbuf_readlink(buf, path, st->st_size) < 0)
 			return error(_("unable to read symlink %s"), path);
 		return 0;
 	case S_IFREG:
 		if (strbuf_read_file(buf, path, st->st_size) != st->st_size)
 			return error(_("unable to open or read %s"), path);
-		convert_to_git(&the_index, path, buf->buf, buf->len, buf, 0);
+		/*
+		 * "git apply" without "--index/--cached" should never look
+		 * at the index; the target file may not have been added to
+		 * the index yet, and we may not even be in any Git repository.
+		 * Pass NULL to convert_to_git() to stress this; the function
+		 * should never look at the index when explicit crlf option
+		 * is given.
+		 */
+		convert_to_git(NULL, path, buf->buf, buf->len, buf, safe_crlf);
 		return 0;
 	default:
 		return -1;
 	}
 }
 
