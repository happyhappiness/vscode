@@ -180,7 +180,7 @@ lz4_reader_bid(struct archive_read_filter_bidder *self,
 			return (0);
 		bits_checked += 8;
 		BD = buffer[5];
-		/* A block maximum size shuld be more than 3. */
+		/* A block maximum size should be more than 3. */
 		if (((BD & 0x70) >> 4) < 4)
 			return (0);
 		/* Reserved bits must be "0". */
@@ -417,7 +417,7 @@ lz4_filter_read_descriptor(struct archive_read_filter *self)
 	/* Reserved bits must be zero. */
 	if (bd & 0x8f)
 		goto malformed_error;
-	/* Get a maxinum block size. */
+	/* Get a maximum block size. */
 	switch (read_buf[1] >> 4) {
 	case 4: /* 64 KB */
 		state->flags.block_maximum_size = 64 * 1024;
@@ -595,7 +595,7 @@ lz4_filter_read_data_block(struct archive_read_filter *self, const void **p)
 #endif
 	}
 
-	/* Check if an error happend in decompression process. */
+	/* Check if an error occurred in the decompression process. */
 	if (uncompressed_size < 0) {
 		archive_set_error(&(self->archive->archive),
 		    ARCHIVE_ERRNO_MISC, "lz4 decompression failed");
@@ -627,7 +627,7 @@ lz4_filter_read_default_stream(struct archive_read_filter *self, const void **p)
 
 	if (state->stage == SELECT_STREAM) {
 		state->stage = READ_DEFAULT_STREAM;
-		/* First, read a desciprtor. */
+		/* First, read a descriptor. */
 		if((ret = lz4_filter_read_descriptor(self)) != ARCHIVE_OK)
 			return (ret);
 		state->stage = READ_DEFAULT_BLOCK;
@@ -706,6 +706,11 @@ lz4_filter_read_legacy_stream(struct archive_read_filter *self, const void **p)
 	/* Make sure we have a whole block. */
 	read_buf = __archive_read_filter_ahead(self->upstream,
 	    4 + compressed, NULL);
+	if (read_buf == NULL) {
+		archive_set_error(&(self->archive->archive),
+		    ARCHIVE_ERRNO_MISC, "truncated lz4 input");
+		return (ARCHIVE_FATAL);
+	}
 	ret = LZ4_decompress_safe(read_buf + 4, state->out_block,
 	    compressed, (int)state->out_block_size);
 	if (ret < 0) {