 
 extern int finalize_object_file(const char *tmpfile, const char *filename);
 
 extern int has_sha1_pack(const unsigned char *sha1);
 
 /*
+ * Open the loose object at path, check its sha1, and return the contents,
+ * type, and size. If the object is a blob, then "contents" may return NULL,
+ * to allow streaming of large blobs.
+ *
+ * Returns 0 on success, negative on error (details may be written to stderr).
+ */
+int read_loose_object(const char *path,
+		      const unsigned char *expected_sha1,
+		      enum object_type *type,
+		      unsigned long *size,
+		      void **contents);
+
+/*
  * Return true iff we have an object named sha1, whether local or in
  * an alternate object database, and whether packed or loose.  This
  * function does not respect replace references.
  *
  * If the QUICK flag is set, do not re-check the pack directory
  * when we cannot find the object (this means we may give a false
