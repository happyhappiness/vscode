@@ -929,7 +929,7 @@ next_entry(struct archive_read_disk *a, struct tree *t,
 		else
 			flags |= FILE_FLAG_SEQUENTIAL_SCAN;
 		t->entry_fh = CreateFileW(tree_current_access_path(t),
-		    GENERIC_READ, 0, NULL, OPEN_EXISTING, flags, NULL);
+		    GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, flags, NULL);
 		if (t->entry_fh == INVALID_HANDLE_VALUE) {
 			archive_set_error(&a->archive, errno,
 			    "Couldn't open %ls", tree_current_path(a->tree));
@@ -1886,7 +1886,7 @@ tree_current_file_information(struct tree *t, BY_HANDLE_FILE_INFORMATION *st,
 	
 	if (sim_lstat && tree_current_is_physical_link(t))
 		flag |= FILE_FLAG_OPEN_REPARSE_POINT;
-	h = CreateFileW(tree_current_access_path(t), 0, 0, NULL,
+	h = CreateFileW(tree_current_access_path(t), 0, FILE_SHARE_READ, NULL,
 	    OPEN_EXISTING, flag, NULL);
 	if (h == INVALID_HANDLE_VALUE) {
 		la_dosmaperr(GetLastError());
@@ -2115,7 +2115,7 @@ archive_read_disk_entry_from_file(struct archive *_a,
 			} else
 				desiredAccess = GENERIC_READ;
 
-			h = CreateFileW(path, desiredAccess, 0, NULL,
+			h = CreateFileW(path, desiredAccess, FILE_SHARE_READ, NULL,
 			    OPEN_EXISTING, flag, NULL);
 			if (h == INVALID_HANDLE_VALUE) {
 				la_dosmaperr(GetLastError());
@@ -2162,7 +2162,7 @@ archive_read_disk_entry_from_file(struct archive *_a,
 		if (fd >= 0) {
 			h = (HANDLE)_get_osfhandle(fd);
 		} else {
-			h = CreateFileW(path, GENERIC_READ, 0, NULL,
+			h = CreateFileW(path, GENERIC_READ, FILE_SHARE_READ, NULL,
 			    OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
 			if (h == INVALID_HANDLE_VALUE) {
 				la_dosmaperr(GetLastError());