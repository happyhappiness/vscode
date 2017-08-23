@@ -322,7 +322,7 @@ struct iso9660 {
 
 	struct archive_string pathname;
 	char	seenRockridge;	/* Set true if RR extensions are used. */
-	char	seenSUSP;	/* Set true if SUSP is beging used. */
+	char	seenSUSP;	/* Set true if SUSP is being used. */
 	char	seenJoliet;
 
 	unsigned char	suspOffset;
@@ -374,7 +374,7 @@ struct iso9660 {
 	size_t		 utf16be_path_len;
 	unsigned char *utf16be_previous_path;
 	size_t		 utf16be_previous_path_len;
-	/* Null buufer used in bidder to improve its performance. */
+	/* Null buffer used in bidder to improve its performance. */
 	unsigned char	 null[2048];
 };
 
@@ -1199,7 +1199,7 @@ archive_read_format_iso9660_read_header(struct archive_read *a,
 			    archive_string_conversion_from_charset(
 				&(a->archive), "UTF-16BE", 1);
 			if (iso9660->sconv_utf16be == NULL)
-				/* Coundn't allocate memory */
+				/* Couldn't allocate memory */
 				return (ARCHIVE_FATAL);
 		}
 		if (iso9660->utf16be_path == NULL) {
@@ -1864,7 +1864,7 @@ parse_file_info(struct archive_read *a, struct file_info *parent,
 		if ((file->utf16be_name = malloc(name_len)) == NULL) {
 			archive_set_error(&a->archive, ENOMEM,
 			    "No memory for file name");
-			return (NULL);
+			goto fail;
 		}
 		memcpy(file->utf16be_name, p, name_len);
 		file->utf16be_bytes = name_len;
@@ -1943,10 +1943,8 @@ parse_file_info(struct archive_read *a, struct file_info *parent,
 			file->symlink_continues = 0;
 			rr_start += iso9660->suspOffset;
 			r = parse_rockridge(a, file, rr_start, rr_end);
-			if (r != ARCHIVE_OK) {
-				free(file);
-				return (NULL);
-			}
+			if (r != ARCHIVE_OK)
+				goto fail;
 			/*
 			 * A file size of symbolic link files in ISO images
 			 * made by makefs is not zero and its location is
@@ -1990,7 +1988,7 @@ parse_file_info(struct archive_read *a, struct file_info *parent,
 				archive_set_error(&a->archive,
 				    ARCHIVE_ERRNO_MISC,
 				    "Invalid Rockridge RE");
-				return (NULL);
+				goto fail;
 			}
 			/*
 			 * Sanity check: file does not have "CL" extension.
@@ -1999,7 +1997,7 @@ parse_file_info(struct archive_read *a, struct file_info *parent,
 				archive_set_error(&a->archive,
 				    ARCHIVE_ERRNO_MISC,
 				    "Invalid Rockridge RE and CL");
-				return (NULL);
+				goto fail;
 			}
 			/*
 			 * Sanity check: The file type must be a directory.
@@ -2008,7 +2006,7 @@ parse_file_info(struct archive_read *a, struct file_info *parent,
 				archive_set_error(&a->archive,
 				    ARCHIVE_ERRNO_MISC,
 				    "Invalid Rockridge RE");
-				return (NULL);
+				goto fail;
 			}
 		} else if (parent != NULL && parent->rr_moved)
 			file->rr_moved_has_re_only = 0;
@@ -2022,7 +2020,7 @@ parse_file_info(struct archive_read *a, struct file_info *parent,
 				archive_set_error(&a->archive,
 				    ARCHIVE_ERRNO_MISC,
 				    "Invalid Rockridge CL");
-				return (NULL);
+				goto fail;
 			}
 			/*
 			 * Sanity check: The file type must be a regular file.
@@ -2031,7 +2029,7 @@ parse_file_info(struct archive_read *a, struct file_info *parent,
 				archive_set_error(&a->archive,
 				    ARCHIVE_ERRNO_MISC,
 				    "Invalid Rockridge CL");
-				return (NULL);
+				goto fail;
 			}
 			parent->subdirs++;
 			/* Overwrite an offset and a number of this "CL" entry
@@ -2049,15 +2047,15 @@ parse_file_info(struct archive_read *a, struct file_info *parent,
 					archive_set_error(&a->archive,
 					    ARCHIVE_ERRNO_MISC,
 					    "Invalid Rockridge CL");
-					return (NULL);
+					goto fail;
 				}
 			}
 			if (file->cl_offset == file->offset ||
 			    parent->rr_moved) {
 				archive_set_error(&a->archive,
 				    ARCHIVE_ERRNO_MISC,
 				    "Invalid Rockridge CL");
-				return (NULL);
+				goto fail;
 			}
 		}
 	}
@@ -2088,6 +2086,10 @@ parse_file_info(struct archive_read *a, struct file_info *parent,
 #endif
 	register_file(iso9660, file);
 	return (file);
+fail:
+	archive_string_free(&file->name);
+	free(file);
+	return (NULL);
 }
 
 static int
@@ -2407,7 +2409,7 @@ read_CE(struct archive_read *a, struct iso9660 *iso9660)
 				return (ARCHIVE_FATAL);
 		} while (heap->cnt &&
 		    heap->reqs[0].offset == iso9660->current_position);
-		/* NOTE: Do not move this consume's code to fron of
+		/* NOTE: Do not move this consume's code to front of
 		 * do-while loop. Registration of nested CE extension
 		 * might cause error because of current position. */
 		__archive_read_consume(a, step);
@@ -2729,7 +2731,7 @@ next_cache_entry(struct archive_read *a, struct iso9660 *iso9660,
 		if (file == NULL) {
 			/*
 			 * If directory entries all which are descendant of
-			 * rr_moved are stil remaning, expose their. 
+			 * rr_moved are still remaining, expose their.
 			 */
 			if (iso9660->re_files.first != NULL && 
 			    iso9660->rr_moved != NULL &&
@@ -2852,15 +2854,15 @@ next_cache_entry(struct archive_read *a, struct iso9660 *iso9660,
 	empty_files.last = &empty_files.first;
 	/* Collect files which has the same file serial number.
 	 * Peek pending_files so that file which number is different
-	 * is not put bak. */
+	 * is not put back. */
 	while (iso9660->pending_files.used > 0 &&
 	    (iso9660->pending_files.files[0]->number == -1 ||
 	     iso9660->pending_files.files[0]->number == number)) {
 		if (file->number == -1) {
 			/* This file has the same offset
 			 * but it's wrong offset which empty files
 			 * and symlink files have.
-			 * NOTE: This wrong offse was recorded by
+			 * NOTE: This wrong offset was recorded by
 			 * old mkisofs utility. If ISO images is
 			 * created by latest mkisofs, this does not
 			 * happen.