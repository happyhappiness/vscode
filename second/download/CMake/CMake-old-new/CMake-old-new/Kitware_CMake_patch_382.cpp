@@ -1,6 +1,6 @@
 /*-
  * Copyright (c) 2003-2007 Tim Kientzle
- * Copyright (c) 2010-2011 Michihiro NAKAJIMA
+ * Copyright (c) 2010-2012 Michihiro NAKAJIMA
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
@@ -242,6 +242,7 @@ archive_read_support_format_cpio(struct archive *_a)
 	    archive_read_format_cpio_read_header,
 	    archive_read_format_cpio_read_data,
 	    archive_read_format_cpio_skip,
+	    NULL,
 	    archive_read_format_cpio_cleanup);
 
 	if (r != ARCHIVE_OK)
@@ -325,7 +326,7 @@ archive_read_format_cpio_options(struct archive_read *a,
 	if (strcmp(key, "compat-2x")  == 0) {
 		/* Handle filnames as libarchive 2.x */
 		cpio->init_default_conversion = (val != NULL)?1:0;
-		ret = ARCHIVE_OK;
+		return (ARCHIVE_OK);
 	} else if (strcmp(key, "hdrcharset")  == 0) {
 		if (val == NULL || val[0] == 0)
 			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
@@ -339,11 +340,13 @@ archive_read_format_cpio_options(struct archive_read *a,
 			else
 				ret = ARCHIVE_FATAL;
 		}
-	} else
-		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
-		    "cpio: unknown keyword ``%s''", key);
+		return (ret);
+	}
 
-	return (ret);
+	/* Note: The "warn" return is just to inform the options
+	 * supervisor that we didn't handle it.  It will generate
+	 * a suitable error if no one used this option. */
+	return (ARCHIVE_WARN);
 }
 
 static int
@@ -396,11 +399,12 @@ archive_read_format_cpio_read_header(struct archive_read *a,
 
 	/* If this is a symlink, read the link contents. */
 	if (archive_entry_filetype(entry) == AE_IFLNK) {
-		h = __archive_read_ahead(a, cpio->entry_bytes_remaining, NULL);
+		h = __archive_read_ahead(a,
+			(size_t)cpio->entry_bytes_remaining, NULL);
 		if (h == NULL)
 			return (ARCHIVE_FATAL);
 		if (archive_entry_copy_symlink_l(entry, (const char *)h,
-		    cpio->entry_bytes_remaining, sconv) != 0) {
+		    (size_t)cpio->entry_bytes_remaining, sconv) != 0) {
 			if (errno == ENOMEM) {
 				archive_set_error(&a->archive, ENOMEM,
 				    "Can't allocate memory for Linkname");
@@ -456,7 +460,7 @@ archive_read_format_cpio_read_data(struct archive_read *a,
 		if (bytes_read <= 0)
 			return (ARCHIVE_FATAL);
 		if (bytes_read > cpio->entry_bytes_remaining)
-			bytes_read = cpio->entry_bytes_remaining;
+			bytes_read = (ssize_t)cpio->entry_bytes_remaining;
 		*size = bytes_read;
 		cpio->entry_bytes_unconsumed = bytes_read;
 		*offset = cpio->entry_offset;
@@ -601,17 +605,23 @@ header_newc(struct archive_read *a, struct cpio *cpio,
 		/* TODO: Abort here? */
 	}
 
-	archive_entry_set_devmajor(entry, atol16(header + newc_devmajor_offset, newc_devmajor_size));
-	archive_entry_set_devminor(entry, atol16(header + newc_devminor_offset, newc_devminor_size));
+	archive_entry_set_devmajor(entry,
+		(dev_t)atol16(header + newc_devmajor_offset, newc_devmajor_size));
+	archive_entry_set_devminor(entry, 
+		(dev_t)atol16(header + newc_devminor_offset, newc_devminor_size));
 	archive_entry_set_ino(entry, atol16(header + newc_ino_offset, newc_ino_size));
-	archive_entry_set_mode(entry, atol16(header + newc_mode_offset, newc_mode_size));
+	archive_entry_set_mode(entry, 
+		(mode_t)atol16(header + newc_mode_offset, newc_mode_size));
 	archive_entry_set_uid(entry, atol16(header + newc_uid_offset, newc_uid_size));
 	archive_entry_set_gid(entry, atol16(header + newc_gid_offset, newc_gid_size));
-	archive_entry_set_nlink(entry, atol16(header + newc_nlink_offset, newc_nlink_size));
-	archive_entry_set_rdevmajor(entry, atol16(header + newc_rdevmajor_offset, newc_rdevmajor_size));
-	archive_entry_set_rdevminor(entry, atol16(header + newc_rdevminor_offset, newc_rdevminor_size));
+	archive_entry_set_nlink(entry,
+		(unsigned int)atol16(header + newc_nlink_offset, newc_nlink_size));
+	archive_entry_set_rdevmajor(entry,
+		(dev_t)atol16(header + newc_rdevmajor_offset, newc_rdevmajor_size));
+	archive_entry_set_rdevminor(entry,
+		(dev_t)atol16(header + newc_rdevminor_offset, newc_rdevminor_size));
 	archive_entry_set_mtime(entry, atol16(header + newc_mtime_offset, newc_mtime_size), 0);
-	*namelength = atol16(header + newc_namesize_offset, newc_namesize_size);
+	*namelength = (size_t)atol16(header + newc_namesize_offset, newc_namesize_size);
 	/* Pad name to 2 more than a multiple of 4. */
 	*name_pad = (2 - *namelength) & 3;
 
@@ -765,15 +775,19 @@ header_odc(struct archive_read *a, struct cpio *cpio,
 	/* Parse out octal fields. */
 	header = (const char *)h;
 
-	archive_entry_set_dev(entry, atol8(header + odc_dev_offset, odc_dev_size));
+	archive_entry_set_dev(entry, 
+		(dev_t)atol8(header + odc_dev_offset, odc_dev_size));
 	archive_entry_set_ino(entry, atol8(header + odc_ino_offset, odc_ino_size));
-	archive_entry_set_mode(entry, atol8(header + odc_mode_offset, odc_mode_size));
+	archive_entry_set_mode(entry, 
+		(mode_t)atol8(header + odc_mode_offset, odc_mode_size));
 	archive_entry_set_uid(entry, atol8(header + odc_uid_offset, odc_uid_size));
 	archive_entry_set_gid(entry, atol8(header + odc_gid_offset, odc_gid_size));
-	archive_entry_set_nlink(entry, atol8(header + odc_nlink_offset, odc_nlink_size));
-	archive_entry_set_rdev(entry, atol8(header + odc_rdev_offset, odc_rdev_size));
+	archive_entry_set_nlink(entry, 
+		(unsigned int)atol8(header + odc_nlink_offset, odc_nlink_size));
+	archive_entry_set_rdev(entry,
+		(dev_t)atol8(header + odc_rdev_offset, odc_rdev_size));
 	archive_entry_set_mtime(entry, atol8(header + odc_mtime_offset, odc_mtime_size), 0);
-	*namelength = atol8(header + odc_namesize_offset, odc_namesize_size);
+	*namelength = (size_t)atol8(header + odc_namesize_offset, odc_namesize_size);
 	*name_pad = 0; /* No padding of filename. */
 
 	/*
@@ -814,15 +828,19 @@ header_afiol(struct archive_read *a, struct cpio *cpio,
 	/* Parse out octal fields. */
 	header = (const char *)h;
 
-	archive_entry_set_dev(entry, atol16(header + afiol_dev_offset, afiol_dev_size));
+	archive_entry_set_dev(entry, 
+		(dev_t)atol16(header + afiol_dev_offset, afiol_dev_size));
 	archive_entry_set_ino(entry, atol16(header + afiol_ino_offset, afiol_ino_size));
-	archive_entry_set_mode(entry, atol8(header + afiol_mode_offset, afiol_mode_size));
+	archive_entry_set_mode(entry,
+		(mode_t)atol8(header + afiol_mode_offset, afiol_mode_size));
 	archive_entry_set_uid(entry, atol16(header + afiol_uid_offset, afiol_uid_size));
 	archive_entry_set_gid(entry, atol16(header + afiol_gid_offset, afiol_gid_size));
-	archive_entry_set_nlink(entry, atol16(header + afiol_nlink_offset, afiol_nlink_size));
-	archive_entry_set_rdev(entry, atol16(header + afiol_rdev_offset, afiol_rdev_size));
+	archive_entry_set_nlink(entry,
+		(unsigned int)atol16(header + afiol_nlink_offset, afiol_nlink_size));
+	archive_entry_set_rdev(entry,
+		(dev_t)atol16(header + afiol_rdev_offset, afiol_rdev_size));
 	archive_entry_set_mtime(entry, atol16(header + afiol_mtime_offset, afiol_mtime_size), 0);
-	*namelength = atol16(header + afiol_namesize_offset, afiol_namesize_size);
+	*namelength = (size_t)atol16(header + afiol_namesize_offset, afiol_namesize_size);
 	*name_pad = 0; /* No padding of filename. */
 
 	cpio->entry_bytes_remaining =