 		free(directions[i]);
 	free(directions);
 
 	return base;
 }
 
-static char *grab_blob(const unsigned char *sha1, unsigned int mode,
+static char *grab_blob(const struct object_id *oid, unsigned int mode,
 		       unsigned long *size, struct userdiff_driver *textconv,
 		       const char *path)
 {
 	char *blob;
 	enum object_type type;
 
 	if (S_ISGITLINK(mode)) {
 		blob = xmalloc(100);
 		*size = snprintf(blob, 100,
-				 "Subproject commit %s\n", sha1_to_hex(sha1));
-	} else if (is_null_sha1(sha1)) {
+				 "Subproject commit %s\n", oid_to_hex(oid));
+	} else if (is_null_oid(oid)) {
 		/* deleted blob */
 		*size = 0;
 		return xcalloc(1, 1);
 	} else if (textconv) {
 		struct diff_filespec *df = alloc_filespec(path);
-		fill_filespec(df, sha1, 1, mode);
+		fill_filespec(df, oid->hash, 1, mode);
 		*size = fill_textconv(textconv, df, &blob);
 		free_filespec(df);
 	} else {
-		blob = read_sha1_file(sha1, &type, size);
+		blob = read_sha1_file(oid->hash, &type, size);
 		if (type != OBJ_BLOB)
-			die("object '%s' is not a blob!", sha1_to_hex(sha1));
+			die("object '%s' is not a blob!", oid_to_hex(oid));
 	}
 	return blob;
 }
 
 static void append_lost(struct sline *sline, int n, const char *line, int len)
 {
