@@ -72,7 +72,7 @@ static int	gzip_filter_close(struct archive_read_filter *);
  *
  * TODO: If zlib is unavailable, gzip_bidder_init() should
  * use the compress_program framework to try to fire up an external
- * gunzip program.
+ * gzip program.
  */
 static int	gzip_bidder_bid(struct archive_read_filter_bidder *,
 		    struct archive_read_filter *);
@@ -100,6 +100,7 @@ archive_read_support_filter_gzip(struct archive *_a)
 		return (ARCHIVE_FATAL);
 
 	bidder->data = NULL;
+	bidder->name = "gzip";
 	bidder->bid = gzip_bidder_bid;
 	bidder->init = gzip_bidder_init;
 	bidder->options = NULL;
@@ -109,7 +110,7 @@ archive_read_support_filter_gzip(struct archive *_a)
 	return (ARCHIVE_OK);
 #else
 	archive_set_error(_a, ARCHIVE_ERRNO_MISC,
-	    "Using external gunzip program");
+	    "Using external gzip program");
 	return (ARCHIVE_WARN);
 #endif
 }
@@ -121,7 +122,7 @@ archive_read_support_filter_gzip(struct archive *_a)
  * number of bytes in header.  If pbits is non-NULL, it receives a
  * count of bits verified, suitable for use by bidder.
  */
-static int
+static ssize_t
 peek_at_header(struct archive_read_filter *filter, int *pbits)
 {
 	const unsigned char *p;
@@ -223,19 +224,19 @@ gzip_bidder_bid(struct archive_read_filter_bidder *self,
 
 /*
  * If we don't have the library on this system, we can't do the
- * decompression directly.  We can, however, try to run gunzip
+ * decompression directly.  We can, however, try to run "gzip -d"
  * in case that's available.
  */
 static int
 gzip_bidder_init(struct archive_read_filter *self)
 {
 	int r;
 
-	r = __archive_read_program(self, "gunzip");
+	r = __archive_read_program(self, "gzip -d");
 	/* Note: We set the format here even if __archive_read_program()
 	 * above fails.  We do, after all, know what the format is
 	 * even if we weren't able to read it. */
-	self->code = ARCHIVE_COMPRESSION_GZIP;
+	self->code = ARCHIVE_FILTER_GZIP;
 	self->name = "gzip";
 	return (r);
 }
@@ -252,7 +253,7 @@ gzip_bidder_init(struct archive_read_filter *self)
 	static const size_t out_block_size = 64 * 1024;
 	void *out_block;
 
-	self->code = ARCHIVE_COMPRESSION_GZIP;
+	self->code = ARCHIVE_FILTER_GZIP;
 	self->name = "gzip";
 
 	state = (struct private_data *)calloc(sizeof(*state), 1);
@@ -299,7 +300,7 @@ consume_header(struct archive_read_filter *self)
 	/* Initialize compression library. */
 	state->stream.next_in = (unsigned char *)(uintptr_t)
 	    __archive_read_filter_ahead(self->upstream, 1, &avail);
-	state->stream.avail_in = avail;
+	state->stream.avail_in = (uInt)avail;
 	ret = inflateInit2(&(state->stream),
 	    -15 /* Don't check for zlib header */);
 
@@ -380,7 +381,7 @@ gzip_filter_read(struct archive_read_filter *self, const void **p)
 
 	/* Empty our output buffer. */
 	state->stream.next_out = state->out_block;
-	state->stream.avail_out = state->out_block_size;
+	state->stream.avail_out = (uInt)state->out_block_size;
 
 	/* Try to fill the output buffer. */
 	while (state->stream.avail_out > 0 && !state->eof) {
@@ -407,7 +408,7 @@ gzip_filter_read(struct archive_read_filter *self, const void **p)
 			    "truncated gzip input");
 			return (ARCHIVE_FATAL);
 		}
-		state->stream.avail_in = avail_in;
+		state->stream.avail_in = (uInt)avail_in;
 
 		/* Decompress and consume some of that data. */
 		ret = inflate(&(state->stream), 0);