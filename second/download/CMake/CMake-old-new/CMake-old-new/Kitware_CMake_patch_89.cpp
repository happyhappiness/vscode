@@ -326,7 +326,7 @@ archive_read_format_cpio_options(struct archive_read *a,
 
 	cpio = (struct cpio *)(a->format->data);
 	if (strcmp(key, "compat-2x")  == 0) {
-		/* Handle filnames as libarchive 2.x */
+		/* Handle filenames as libarchive 2.x */
 		cpio->init_default_conversion = (val != NULL)?1:0;
 		return (ARCHIVE_OK);
 	} else if (strcmp(key, "hdrcharset")  == 0) {
@@ -356,7 +356,7 @@ archive_read_format_cpio_read_header(struct archive_read *a,
     struct archive_entry *entry)
 {
 	struct cpio *cpio;
-	const void *h;
+	const void *h, *hl;
 	struct archive_string_conv *sconv;
 	size_t namelength;
 	size_t name_pad;
@@ -406,11 +406,11 @@ archive_read_format_cpio_read_header(struct archive_read *a,
 			    "Rejecting malformed cpio archive: symlink contents exceed 1 megabyte");
 			return (ARCHIVE_FATAL);
 		}
-		h = __archive_read_ahead(a,
+		hl = __archive_read_ahead(a,
 			(size_t)cpio->entry_bytes_remaining, NULL);
-		if (h == NULL)
+		if (hl == NULL)
 			return (ARCHIVE_FATAL);
-		if (archive_entry_copy_symlink_l(entry, (const char *)h,
+		if (archive_entry_copy_symlink_l(entry, (const char *)hl,
 		    (size_t)cpio->entry_bytes_remaining, sconv) != 0) {
 			if (errno == ENOMEM) {
 				archive_set_error(&a->archive, ENOMEM,
@@ -434,7 +434,8 @@ archive_read_format_cpio_read_header(struct archive_read *a,
 	 * header.  XXX */
 
 	/* Compare name to "TRAILER!!!" to test for end-of-archive. */
-	if (namelength == 11 && strcmp((const char *)h, "TRAILER!!!") == 0) {
+	if (namelength == 11 && strncmp((const char *)h, "TRAILER!!!",
+	    11) == 0) {
 		/* TODO: Store file location of start of block. */
 		archive_clear_error(&a->archive);
 		return (ARCHIVE_EOF);
@@ -814,8 +815,8 @@ header_odc(struct archive_read *a, struct cpio *cpio,
  * NOTE: if a filename suffix is ".z", it is the file gziped by afio.
  * it would be nice that we can show uncompressed file size and we can
  * uncompressed file contents automatically, unfortunately we have nothing
- * to get a uncompressed file size while reading each header. it means
- * we also cannot uncompressed file contens under the our framework.
+ * to get a uncompressed file size while reading each header. It means
+ * we also cannot uncompress file contents under our framework.
  */
 static int
 header_afiol(struct archive_read *a, struct cpio *cpio,