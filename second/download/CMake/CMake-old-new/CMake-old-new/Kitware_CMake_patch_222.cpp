@@ -68,6 +68,7 @@ struct archive_write_program_data {
 
 	char		*child_buf;
 	size_t		 child_buf_len, child_buf_avail;
+	char		*program_name;
 };
 
 struct private_data {
@@ -105,7 +106,7 @@ archive_write_add_filter_program(struct archive *_a, const char *cmd)
 	if (data->cmd == NULL)
 		goto memerr;
 
-	data->pdata = __archive_write_program_allocate();
+	data->pdata = __archive_write_program_allocate(cmd);
 	if (data->pdata == NULL)
 		goto memerr;
 
@@ -174,7 +175,7 @@ archive_compressor_program_free(struct archive_write_filter *f)
  * Allocate resources for executing an external program.
  */
 struct archive_write_program_data *
-__archive_write_program_allocate(void)
+__archive_write_program_allocate(const char *program)
 {
 	struct archive_write_program_data *data;
 
@@ -183,6 +184,7 @@ __archive_write_program_allocate(void)
 		return (data);
 	data->child_stdin = -1;
 	data->child_stdout = -1;
+	data->program_name = strdup(program);
 	return (data);
 }
 
@@ -231,7 +233,7 @@ __archive_write_program_open(struct archive_write_filter *f,
 		    &data->child_stdout);
 	if (child == -1) {
 		archive_set_error(f->archive, EINVAL,
-		    "Can't initialise filter");
+		    "Can't launch external program: %s", cmd);
 		return (ARCHIVE_FATAL);
 	}
 #if defined(_WIN32) && !defined(__CYGWIN__)
@@ -242,7 +244,7 @@ __archive_write_program_open(struct archive_write_filter *f,
 		close(data->child_stdout);
 		data->child_stdout = -1;
 		archive_set_error(f->archive, EINVAL,
-		    "Can't initialise filter");
+		    "Can't launch external program: %s", cmd);
 		return (ARCHIVE_FATAL);
 	}
 #else
@@ -334,7 +336,7 @@ __archive_write_program_write(struct archive_write_filter *f,
 		ret = child_write(f, data, buf, length);
 		if (ret == -1 || ret == 0) {
 			archive_set_error(f->archive, EIO,
-			    "Can't write to filter");
+			    "Can't write to program: %s", data->program_name);
 			return (ARCHIVE_FATAL);
 		}
 		length -= ret;
@@ -373,7 +375,7 @@ __archive_write_program_close(struct archive_write_filter *f,
 
 		if (bytes_read == -1) {
 			archive_set_error(f->archive, errno,
-			    "Read from filter failed unexpectedly.");
+			    "Error reading from program: %s", data->program_name);
 			ret = ARCHIVE_FATAL;
 			goto cleanup;
 		}
@@ -403,7 +405,7 @@ __archive_write_program_close(struct archive_write_filter *f,
 
 	if (status != 0) {
 		archive_set_error(f->archive, EIO,
-		    "Filter exited with failure.");
+		    "Error closing program: %s", data->program_name);
 		ret = ARCHIVE_FATAL;
 	}
 	r1 = __archive_write_close_filter(f->next_filter);