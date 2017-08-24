@@ -1962,7 +1962,7 @@ parse_file_info(struct archive_read *a, struct file_info *parent,
 		    (parent->re || parent->re_descendant))
 			file->re_descendant = 1;
 		if (file->cl_offset) {
-			struct file_info *p;
+			struct file_info *r;
 
 			if (parent == NULL || parent->parent == NULL) {
 				archive_set_error(&a->archive,
@@ -1990,8 +1990,8 @@ parse_file_info(struct archive_read *a, struct file_info *parent,
 			 * Sanity check: cl_offset does not point at its
 			 * the parents or itself.
 			 */
-			for (p = parent; p; p = p->parent) {
-				if (p->offset == file->cl_offset) {
+			for (r = parent; r; r = r->parent) {
+				if (r->offset == file->cl_offset) {
 					archive_set_error(&a->archive,
 					    ARCHIVE_ERRNO_MISC,
 					    "Invalid Rockridge CL");