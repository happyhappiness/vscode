 extern struct packed_git *find_sha1_pack(const unsigned char *sha1,
 					 struct packed_git *packs);
 
 extern void pack_report(void);
 
 /*
+ * Create a temporary file rooted in the object database directory.
+ */
+extern int odb_mkstemp(char *template, size_t limit, const char *pattern);
+
+/*
+ * Generate the filename to be used for a pack file with checksum "sha1" and
+ * extension "ext". The result is written into the strbuf "buf", overwriting
+ * any existing contents. A pointer to buf->buf is returned as a convenience.
+ *
+ * Example: odb_pack_name(out, sha1, "idx") => ".git/objects/pack/pack-1234..idx"
+ */
+extern char *odb_pack_name(struct strbuf *buf, const unsigned char *sha1, const char *ext);
+
+/*
+ * Create a pack .keep file named "name" (which should generally be the output
+ * of odb_pack_name). Returns a file descriptor opened for writing, or -1 on
+ * error.
+ */
+extern int odb_pack_keep(const char *name);
+
+/*
  * mmap the index file for the specified packfile (if it is not
  * already mmapped).  Return 0 on success.
  */
 extern int open_pack_index(struct packed_git *);
 
 /*
