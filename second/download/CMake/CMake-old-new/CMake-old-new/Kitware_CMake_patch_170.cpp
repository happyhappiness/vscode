@@ -1046,7 +1046,7 @@ setup_sparse(struct archive_read_disk *a,
 	struct fiemap *fm;
 	struct fiemap_extent *fe;
 	int64_t size;
-	int count, do_fiemap;
+	int count, do_fiemap, iters;
 	int exit_sts = ARCHIVE_OK;
 
 	if (archive_entry_filetype(entry) != AE_IFREG
@@ -1083,7 +1083,7 @@ setup_sparse(struct archive_read_disk *a,
 	fm->fm_extent_count = count;
 	do_fiemap = 1;
 	size = archive_entry_size(entry);
-	for (;;) {
+	for (iters = 0; ; ++iters) {
 		int i, r;
 
 		r = ioctl(*fd, FS_IOC_FIEMAP, fm); 
@@ -1093,8 +1093,13 @@ setup_sparse(struct archive_read_disk *a,
 			 * version(<2.6.28) cannot perfom FS_IOC_FIEMAP. */
 			goto exit_setup_sparse;
 		}
-		if (fm->fm_mapped_extents == 0)
+		if (fm->fm_mapped_extents == 0) {
+			if (iters == 0) {
+				/* Fully sparse file; insert a zero-length "data" entry */
+				archive_entry_sparse_add_entry(entry, 0, 0);
+			}
 			break;
+		}
 		fe = fm->fm_extents;
 		for (i = 0; i < (int)fm->fm_mapped_extents; i++, fe++) {
 			if (!(fe->fe_flags & FIEMAP_EXTENT_UNWRITTEN)) {
@@ -1139,6 +1144,7 @@ setup_sparse(struct archive_read_disk *a,
 	off_t initial_off; /* FreeBSD/Solaris only, so off_t okay here */
 	off_t off_s, off_e; /* FreeBSD/Solaris only, so off_t okay here */
 	int exit_sts = ARCHIVE_OK;
+	int check_fully_sparse = 0;
 
 	if (archive_entry_filetype(entry) != AE_IFREG
 	    || archive_entry_size(entry) <= 0
@@ -1191,8 +1197,14 @@ setup_sparse(struct archive_read_disk *a,
 	while (off_s < size) {
 		off_s = lseek(*fd, off_s, SEEK_DATA);
 		if (off_s == (off_t)-1) {
-			if (errno == ENXIO)
-				break;/* no more hole */
+			if (errno == ENXIO) {
+				/* no more hole */
+				if (archive_entry_sparse_count(entry) == 0) {
+					/* Potentially a fully-sparse file. */
+					check_fully_sparse = 1;
+				}
+				break;
+			}
 			archive_set_error(&a->archive, errno,
 			    "lseek(SEEK_HOLE) failed");
 			exit_sts = ARCHIVE_FAILED;
@@ -1216,6 +1228,14 @@ setup_sparse(struct archive_read_disk *a,
 			off_e - off_s);
 		off_s = off_e;
 	}
+
+	if (check_fully_sparse) {
+		if (lseek(*fd, 0, SEEK_HOLE) == 0 &&
+			lseek(*fd, 0, SEEK_END) == size) {
+			/* Fully sparse file; insert a zero-length "data" entry */
+			archive_entry_sparse_add_entry(entry, 0, 0);
+		}
+	}
 exit_setup_sparse:
 	lseek(*fd, initial_off, SEEK_SET);
 	return (exit_sts);