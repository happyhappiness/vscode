 	char *buf = xstrdup(path);
 	enum scld_error result = safe_create_leading_directories(buf);
 	free(buf);
 	return result;
 }
 
-static void fill_sha1_path(char *pathbuf, const unsigned char *sha1)
+static void fill_sha1_path(struct strbuf *buf, const unsigned char *sha1)
 {
 	int i;
 	for (i = 0; i < 20; i++) {
 		static char hex[] = "0123456789abcdef";
 		unsigned int val = sha1[i];
-		char *pos = pathbuf + i*2 + (i > 0);
-		*pos++ = hex[val >> 4];
-		*pos = hex[val & 0xf];
+		strbuf_addch(buf, hex[val >> 4]);
+		strbuf_addch(buf, hex[val & 0xf]);
+		if (!i)
+			strbuf_addch(buf, '/');
 	}
 }
 
 const char *sha1_file_name(const unsigned char *sha1)
 {
-	static char buf[PATH_MAX];
-	const char *objdir;
-	int len;
-
-	objdir = get_object_directory();
-	len = strlen(objdir);
-
-	/* '/' + sha1(2) + '/' + sha1(38) + '\0' */
-	if (len + 43 > PATH_MAX)
-		die("insanely long object directory %s", objdir);
-	memcpy(buf, objdir, len);
-	buf[len] = '/';
-	buf[len+3] = '/';
-	buf[len+42] = '\0';
-	fill_sha1_path(buf + len + 1, sha1);
-	return buf;
+	static struct strbuf buf = STRBUF_INIT;
+
+	strbuf_reset(&buf);
+	strbuf_addf(&buf, "%s/", get_object_directory());
+
+	fill_sha1_path(&buf, sha1);
+	return buf.buf;
+}
+
+struct strbuf *alt_scratch_buf(struct alternate_object_database *alt)
+{
+	strbuf_setlen(&alt->scratch, alt->base_len);
+	return &alt->scratch;
+}
+
+static const char *alt_sha1_path(struct alternate_object_database *alt,
+				 const unsigned char *sha1)
+{
+	struct strbuf *buf = alt_scratch_buf(alt);
+	fill_sha1_path(buf, sha1);
+	return buf->buf;
 }
 
 /*
  * Return the name of the pack or index file with the specified sha1
  * in its filename.  *base and *name are scratch space that must be
  * provided by the caller.  which should be "pack" or "idx".
