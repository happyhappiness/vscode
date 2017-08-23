@@ -222,7 +222,7 @@ file_open(struct archive *a, void *client_data)
 	void *buffer;
 	const char *filename = NULL;
 	const wchar_t *wfilename = NULL;
-	int fd;
+	int fd = -1;
 	int is_disk_like = 0;
 #if defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
 	off_t mediasize = 0; /* FreeBSD-specific, so off_t okay here. */
@@ -277,7 +277,7 @@ file_open(struct archive *a, void *client_data)
 #else
 		archive_set_error(a, ARCHIVE_ERRNO_MISC,
 		    "Unexpedted operation in archive_read_open_filename");
-		return (ARCHIVE_FATAL);
+		goto fail;
 #endif
 	}
 	if (fstat(fd, &st) != 0) {
@@ -287,7 +287,7 @@ file_open(struct archive *a, void *client_data)
 		else
 			archive_set_error(a, errno, "Can't stat '%s'",
 			    filename);
-		return (ARCHIVE_FATAL);
+		goto fail;
 	}
 
 	/*
@@ -356,11 +356,9 @@ file_open(struct archive *a, void *client_data)
 		mine->block_size = new_block_size;
 	}
 	buffer = malloc(mine->block_size);
-	if (mine == NULL || buffer == NULL) {
+	if (buffer == NULL) {
 		archive_set_error(a, ENOMEM, "No memory");
-		free(mine);
-		free(buffer);
-		return (ARCHIVE_FATAL);
+		goto fail;
 	}
 	mine->buffer = buffer;
 	mine->fd = fd;
@@ -372,6 +370,14 @@ file_open(struct archive *a, void *client_data)
 		mine->use_lseek = 1;
 
 	return (ARCHIVE_OK);
+fail:
+	/*
+	 * Don't close file descriptors not opened or ones pointing referring
+	 * to `FNT_STDIN`.
+	 */
+	if (fd != -1 && fd != 0)
+		close(fd);
+	return (ARCHIVE_FATAL);
 }
 
 static ssize_t