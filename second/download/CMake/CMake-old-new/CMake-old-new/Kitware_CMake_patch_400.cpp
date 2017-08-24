@@ -136,6 +136,7 @@ archive_read_support_filter_xz(struct archive *_a)
 		return (ARCHIVE_FATAL);
 
 	bidder->data = NULL;
+	bidder->name = "xz";
 	bidder->bid = xz_bidder_bid;
 	bidder->init = xz_bidder_init;
 	bidder->options = NULL;
@@ -144,7 +145,7 @@ archive_read_support_filter_xz(struct archive *_a)
 	return (ARCHIVE_OK);
 #else
 	archive_set_error(_a, ARCHIVE_ERRNO_MISC,
-	    "Using external unxz program for xz decompression");
+	    "Using external xz program for xz decompression");
 	return (ARCHIVE_WARN);
 #endif
 }
@@ -170,6 +171,7 @@ archive_read_support_filter_lzma(struct archive *_a)
 		return (ARCHIVE_FATAL);
 
 	bidder->data = NULL;
+	bidder->name = "lzma";
 	bidder->bid = lzma_bidder_bid;
 	bidder->init = lzma_bidder_init;
 	bidder->options = NULL;
@@ -180,7 +182,7 @@ archive_read_support_filter_lzma(struct archive *_a)
 	return (ARCHIVE_OK);
 #else
 	archive_set_error(_a, ARCHIVE_ERRNO_MISC,
-	    "Using external unlzma program for lzma decompression");
+	    "Using external lzma program for lzma decompression");
 	return (ARCHIVE_WARN);
 #endif
 }
@@ -207,6 +209,7 @@ archive_read_support_filter_lzip(struct archive *_a)
 		return (ARCHIVE_FATAL);
 
 	bidder->data = NULL;
+	bidder->name = "lzip";
 	bidder->bid = lzip_bidder_bid;
 	bidder->init = lzip_bidder_init;
 	bidder->options = NULL;
@@ -415,23 +418,23 @@ lzip_bidder_bid(struct archive_read_filter_bidder *self,
 static int
 xz_bidder_init(struct archive_read_filter *self)
 {
-	self->code = ARCHIVE_COMPRESSION_XZ;
+	self->code = ARCHIVE_FILTER_XZ;
 	self->name = "xz";
 	return (xz_lzma_bidder_init(self));
 }
 
 static int
 lzma_bidder_init(struct archive_read_filter *self)
 {
-	self->code = ARCHIVE_COMPRESSION_LZMA;
+	self->code = ARCHIVE_FILTER_LZMA;
 	self->name = "lzma";
 	return (xz_lzma_bidder_init(self));
 }
 
 static int
 lzip_bidder_init(struct archive_read_filter *self)
 {
-	self->code = ARCHIVE_COMPRESSION_LZIP;
+	self->code = ARCHIVE_FILTER_LZIP;
 	self->name = "lzip";
 	return (xz_lzma_bidder_init(self));
 }
@@ -518,7 +521,7 @@ xz_lzma_bidder_init(struct archive_read_filter *self)
 	state->stream.avail_out = state->out_block_size;
 
 	state->crc32 = 0;
-	if (self->code == ARCHIVE_COMPRESSION_LZIP) {
+	if (self->code == ARCHIVE_FILTER_LZIP) {
 		/*
 		 * We have to read a lzip header and use it to initialize
 		 * compression library, thus we cannot initialize the
@@ -530,7 +533,7 @@ xz_lzma_bidder_init(struct archive_read_filter *self)
 		state->in_stream = 1;
 
 	/* Initialize compression library. */
-	if (self->code == ARCHIVE_COMPRESSION_XZ)
+	if (self->code == ARCHIVE_FILTER_XZ)
 		ret = lzma_stream_decoder(&(state->stream),
 		    LZMA_MEMLIMIT,/* memlimit */
 		    LZMA_CONCATENATED);
@@ -730,7 +733,7 @@ xz_filter_read(struct archive_read_filter *self, const void **p)
 		*p = NULL;
 	else {
 		*p = state->out_block;
-		if (self->code == ARCHIVE_COMPRESSION_LZIP) {
+		if (self->code == ARCHIVE_FILTER_LZIP) {
 			state->crc32 = lzma_crc32(state->out_block,
 			    decompressed, state->crc32);
 			if (state->eof) {
@@ -778,7 +781,7 @@ lzma_bidder_init(struct archive_read_filter *self)
 	struct private_data *state;
 	ssize_t ret, avail_in;
 
-	self->code = ARCHIVE_COMPRESSION_LZMA;
+	self->code = ARCHIVE_FILTER_LZMA;
 	self->name = "lzma";
 
 	state = (struct private_data *)calloc(sizeof(*state), 1);
@@ -941,11 +944,11 @@ lzma_bidder_init(struct archive_read_filter *self)
 {
 	int r;
 
-	r = __archive_read_program(self, "unlzma");
+	r = __archive_read_program(self, "lzma -d -qq");
 	/* Note: We set the format here even if __archive_read_program()
 	 * above fails.  We do, after all, know what the format is
 	 * even if we weren't able to read it. */
-	self->code = ARCHIVE_COMPRESSION_LZMA;
+	self->code = ARCHIVE_FILTER_LZMA;
 	self->name = "lzma";
 	return (r);
 }
@@ -958,11 +961,11 @@ xz_bidder_init(struct archive_read_filter *self)
 {
 	int r;
 
-	r = __archive_read_program(self, "unxz");
+	r = __archive_read_program(self, "xz -d -qq");
 	/* Note: We set the format here even if __archive_read_program()
 	 * above fails.  We do, after all, know what the format is
 	 * even if we weren't able to read it. */
-	self->code = ARCHIVE_COMPRESSION_XZ;
+	self->code = ARCHIVE_FILTER_XZ;
 	self->name = "xz";
 	return (r);
 }
@@ -972,11 +975,11 @@ lzip_bidder_init(struct archive_read_filter *self)
 {
 	int r;
 
-	r = __archive_read_program(self, "unlzip");
+	r = __archive_read_program(self, "lzip -d -q");
 	/* Note: We set the format here even if __archive_read_program()
 	 * above fails.  We do, after all, know what the format is
 	 * even if we weren't able to read it. */
-	self->code = ARCHIVE_COMPRESSION_LZIP;
+	self->code = ARCHIVE_FILTER_LZIP;
 	self->name = "lzip";
 	return (r);
 }