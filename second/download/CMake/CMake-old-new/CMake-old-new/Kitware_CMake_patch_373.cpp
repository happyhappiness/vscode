@@ -119,7 +119,8 @@ file_read(struct archive *a, void *client_data, const void **buff)
 		if (bytes_read < 0) {
 			if (errno == EINTR)
 				continue;
-			archive_set_error(a, errno, "Error reading fd %d", mine->fd);
+			archive_set_error(a, errno, "Error reading fd %d",
+			    mine->fd);
 		}
 		return (bytes_read);
 	}
@@ -129,8 +130,8 @@ static int64_t
 file_skip(struct archive *a, void *client_data, int64_t request)
 {
 	struct read_fd_data *mine = (struct read_fd_data *)client_data;
-	off_t skip = (off_t)request;
-	off_t old_offset, new_offset;
+	int64_t skip = request;
+	int64_t old_offset, new_offset;
 	int skip_bits = sizeof(skip) * 8 - 1;  /* off_t is a signed type. */
 
 	if (!mine->use_lseek)