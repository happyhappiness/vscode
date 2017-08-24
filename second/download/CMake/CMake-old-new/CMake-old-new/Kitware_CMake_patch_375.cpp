@@ -94,6 +94,7 @@ archive_read_support_filter_bzip2(struct archive *_a)
 		return (ARCHIVE_FATAL);
 
 	reader->data = NULL;
+	reader->name = "bzip2";
 	reader->bid = bzip2_reader_bid;
 	reader->init = bzip2_reader_init;
 	reader->options = NULL;
@@ -102,7 +103,7 @@ archive_read_support_filter_bzip2(struct archive *_a)
 	return (ARCHIVE_OK);
 #else
 	archive_set_error(_a, ARCHIVE_ERRNO_MISC,
-	    "Using external bunzip2 program");
+	    "Using external bzip2 program");
 	return (ARCHIVE_WARN);
 #endif
 }
@@ -170,11 +171,11 @@ bzip2_reader_init(struct archive_read_filter *self)
 {
 	int r;
 
-	r = __archive_read_program(self, "bunzip2");
+	r = __archive_read_program(self, "bzip2 -d");
 	/* Note: We set the format here even if __archive_read_program()
 	 * above fails.  We do, after all, know what the format is
 	 * even if we weren't able to read it. */
-	self->code = ARCHIVE_COMPRESSION_BZIP2;
+	self->code = ARCHIVE_FILTER_BZIP2;
 	self->name = "bzip2";
 	return (r);
 }
@@ -192,7 +193,7 @@ bzip2_reader_init(struct archive_read_filter *self)
 	void *out_block;
 	struct private_data *state;
 
-	self->code = ARCHIVE_COMPRESSION_BZIP2;
+	self->code = ARCHIVE_FILTER_BZIP2;
 	self->name = "bzip2";
 
 	state = (struct private_data *)calloc(sizeof(*state), 1);