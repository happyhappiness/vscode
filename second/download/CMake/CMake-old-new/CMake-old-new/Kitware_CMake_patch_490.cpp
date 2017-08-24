@@ -479,23 +479,23 @@ archive_write_pax_header(struct archive_write *a,
     path = archive_entry_pathname(entry_main);
     path_w = archive_entry_pathname_w(entry_main);
     if (path != NULL && path_w == NULL) {
-        archive_set_error(&a->archive, EILSEQ,
+        archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
             "Can't translate pathname '%s' to UTF-8", path);
         ret = ARCHIVE_WARN;
         hdrcharset = "BINARY";
     }
     uname = archive_entry_uname(entry_main);
     uname_w = archive_entry_uname_w(entry_main);
     if (uname != NULL && uname_w == NULL) {
-        archive_set_error(&a->archive, EILSEQ,
+        archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
             "Can't translate uname '%s' to UTF-8", uname);
         ret = ARCHIVE_WARN;
         hdrcharset = "BINARY";
     }
     gname = archive_entry_gname(entry_main);
     gname_w = archive_entry_gname_w(entry_main);
     if (gname != NULL && gname_w == NULL) {
-        archive_set_error(&a->archive, EILSEQ,
+        archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
             "Can't translate gname '%s' to UTF-8", gname);
         ret = ARCHIVE_WARN;
         hdrcharset = "BINARY";
@@ -509,7 +509,7 @@ archive_write_pax_header(struct archive_write *a,
             linkpath_w = archive_entry_symlink_w(entry_main);
     }
     if (linkpath != NULL && linkpath_w == NULL) {
-        archive_set_error(&a->archive, EILSEQ,
+        archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
             "Can't translate linkpath '%s' to UTF-8", linkpath);
         ret = ARCHIVE_WARN;
         hdrcharset = "BINARY";