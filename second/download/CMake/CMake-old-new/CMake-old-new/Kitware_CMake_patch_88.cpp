@@ -104,13 +104,12 @@ archive_read_support_format_ar(struct archive *_a)
 	archive_check_magic(_a, ARCHIVE_READ_MAGIC,
 	    ARCHIVE_STATE_NEW, "archive_read_support_format_ar");
 
-	ar = (struct ar *)malloc(sizeof(*ar));
+	ar = (struct ar *)calloc(1, sizeof(*ar));
 	if (ar == NULL) {
 		archive_set_error(&a->archive, ENOMEM,
 		    "Can't allocate ar data");
 		return (ARCHIVE_FATAL);
 	}
-	memset(ar, 0, sizeof(*ar));
 	ar->strtab = NULL;
 
 	r = __archive_read_register_format(a,
@@ -260,7 +259,7 @@ _ar_read_header(struct archive_read *a, struct archive_entry *entry,
 		archive_entry_set_filetype(entry, AE_IFREG);
 		/* Get the size of the filename table. */
 		number = ar_atol10(h + AR_size_offset, AR_size_size);
-		if (number > SIZE_MAX) {
+		if (number > SIZE_MAX || number > 1024 * 1024 * 1024) {
 			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
 			    "Filename table too large");
 			return (ARCHIVE_FATAL);
@@ -316,7 +315,7 @@ _ar_read_header(struct archive_read *a, struct archive_entry *entry,
 		 * If we can't look up the real name, warn and return
 		 * the entry with the wrong name.
 		 */
-		if (ar->strtab == NULL || number > ar->strtab_size) {
+		if (ar->strtab == NULL || number >= ar->strtab_size) {
 			archive_set_error(&a->archive, EINVAL,
 			    "Can't find long filename for GNU/SVR4 archive entry");
 			archive_entry_copy_pathname(entry, filename);
@@ -342,16 +341,19 @@ _ar_read_header(struct archive_read *a, struct archive_entry *entry,
 
 		/* Parse the size of the name, adjust the file size. */
 		number = ar_atol10(h + AR_name_offset + 3, AR_name_size - 3);
-		bsd_name_length = (size_t)number;
-		/* Guard against the filename + trailing NUL
-		 * overflowing a size_t and against the filename size
-		 * being larger than the entire entry. */
-		if (number > (uint64_t)(bsd_name_length + 1)
-		    || (int64_t)bsd_name_length > ar->entry_bytes_remaining) {
+		/* Sanity check the filename length:
+		 *   = Must be <= SIZE_MAX - 1
+		 *   = Must be <= 1MB
+		 *   = Cannot be bigger than the entire entry
+		 */
+		if (number > SIZE_MAX - 1
+		    || number > 1024 * 1024
+		    || (int64_t)number > ar->entry_bytes_remaining) {
 			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
 			    "Bad input file size");
 			return (ARCHIVE_FATAL);
 		}
+		bsd_name_length = (size_t)number;
 		ar->entry_bytes_remaining -= bsd_name_length;
 		/* Adjust file size reported to client. */
 		archive_entry_set_size(entry, ar->entry_bytes_remaining);