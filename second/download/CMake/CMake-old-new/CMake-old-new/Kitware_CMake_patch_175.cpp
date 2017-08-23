@@ -54,14 +54,14 @@ __FBSDID("$FreeBSD$");
 
 struct private_data {
 	int		 compression_level;
-	uint8_t		 header_written:1;
-	uint8_t		 version_number:1;
-	uint8_t		 block_independence:1;
-	uint8_t		 block_checksum:1;
-	uint8_t		 stream_size:1;
-	uint8_t		 stream_checksum:1;
-	uint8_t		 preset_dictionary:1;
-	uint8_t		 block_maximum_size:3;
+	unsigned	 header_written:1;
+	unsigned	 version_number:1;
+	unsigned	 block_independence:1;
+	unsigned	 block_checksum:1;
+	unsigned	 stream_size:1;
+	unsigned	 stream_checksum:1;
+	unsigned	 preset_dictionary:1;
+	unsigned	 block_maximum_size:3;
 #if defined(HAVE_LIBLZ4) && LZ4_VERSION_MAJOR >= 1 && LZ4_VERSION_MINOR >= 2
 	int64_t		 total_in;
 	char		*out;
@@ -137,7 +137,7 @@ archive_write_add_filter_lz4(struct archive *_a)
 	 * We don't have lz4 library, and execute external lz4 program
 	 * instead.
 	 */
-	data->pdata = __archive_write_program_allocate();
+	data->pdata = __archive_write_program_allocate("lz4");
 	if (data->pdata == NULL) {
 		free(data);
 		archive_set_error(&a->archive, ENOMEM, "Out of memory");
@@ -160,10 +160,20 @@ archive_filter_lz4_options(struct archive_write_filter *f,
 	struct private_data *data = (struct private_data *)f->data;
 
 	if (strcmp(key, "compression-level") == 0) {
-		if (value == NULL || !(value[0] >= '1' && value[0] <= '9') ||
+		int val;
+		if (value == NULL || !((val = value[0] - '0') >= 1 && val <= 9) ||
 		    value[1] != '\0')
 			return (ARCHIVE_WARN);
-		data->compression_level = value[0] - '0';
+
+#ifndef HAVE_LZ4HC_H
+		if(val >= 3)
+		{
+			archive_set_error(f->archive, ARCHIVE_ERRNO_PROGRAMMER,
+				"High compression not included in this build");
+			return (ARCHIVE_FATAL);
+		}
+#endif
+		data->compression_level = val;
 		return (ARCHIVE_OK);
 	}
 	if (strcmp(key, "stream-checksum") == 0) {
@@ -367,14 +377,20 @@ archive_filter_lz4_free(struct archive_write_filter *f)
 	struct private_data *data = (struct private_data *)f->data;
 
 	if (data->lz4_stream != NULL) {
-		if (data->compression_level < 3)
+#ifdef HAVE_LZ4HC_H
+		if (data->compression_level >= 3)
+#if LZ4_VERSION_MAJOR >= 1 && LZ4_VERSION_MINOR >= 7
+			LZ4_freeStreamHC(data->lz4_stream);
+#else
+			LZ4_freeHC(data->lz4_stream);
+#endif
+		else
+#endif
 #if LZ4_VERSION_MINOR >= 3
 			LZ4_freeStream(data->lz4_stream);
 #else
 			LZ4_free(data->lz4_stream);
 #endif
-		else
-			LZ4_freeHC(data->lz4_stream);
 	}
 	free(data->out_buffer);
 	free(data->in_buffer_allocated);
@@ -481,13 +497,26 @@ drive_compressor_independence(struct archive_write_filter *f, const char *p,
 	struct private_data *data = (struct private_data *)f->data;
 	unsigned int outsize;
 
-	if (data->compression_level < 4)
-		outsize = LZ4_compress_limitedOutput(p, data->out + 4,
-		    (int)length, (int)data->block_size);
-	else
+#ifdef HAVE_LZ4HC_H
+	if (data->compression_level >= 3)
+#if LZ4_VERSION_MAJOR >= 1 && LZ4_VERSION_MINOR >= 7
+		outsize = LZ4_compress_HC(p, data->out + 4,
+		     (int)length, (int)data->block_size,
+		    data->compression_level);
+#else
 		outsize = LZ4_compressHC2_limitedOutput(p, data->out + 4,
 		    (int)length, (int)data->block_size,
 		    data->compression_level);
+#endif
+	else
+#endif
+#if LZ4_VERSION_MAJOR >= 1 && LZ4_VERSION_MINOR >= 7
+		outsize = LZ4_compress_default(p, data->out + 4,
+		    (int)length, (int)data->block_size);
+#else
+		outsize = LZ4_compress_limitedOutput(p, data->out + 4,
+		    (int)length, (int)data->block_size);
+#endif
 
 	if (outsize) {
 		/* The buffer is compressed. */
@@ -518,33 +547,60 @@ drive_compressor_dependence(struct archive_write_filter *f, const char *p,
 	struct private_data *data = (struct private_data *)f->data;
 	int outsize;
 
-	if (data->compression_level < 3) {
+#define DICT_SIZE	(64 * 1024)
+#ifdef HAVE_LZ4HC_H
+	if (data->compression_level >= 3) {
 		if (data->lz4_stream == NULL) {
-			data->lz4_stream = LZ4_createStream();
+#if LZ4_VERSION_MAJOR >= 1 && LZ4_VERSION_MINOR >= 7
+			data->lz4_stream = LZ4_createStreamHC();
+			LZ4_resetStreamHC(data->lz4_stream, data->compression_level);
+#else
+			data->lz4_stream =
+			    LZ4_createHC(data->in_buffer_allocated);
+#endif
 			if (data->lz4_stream == NULL) {
 				archive_set_error(f->archive, ENOMEM,
 				    "Can't allocate data for compression"
 				    " buffer");
 				return (ARCHIVE_FATAL);
 			}
 		}
-		outsize = LZ4_compress_limitedOutput_continue(
+		else
+			LZ4_loadDictHC(data->lz4_stream, data->in_buffer_allocated, DICT_SIZE);
+
+#if LZ4_VERSION_MAJOR >= 1 && LZ4_VERSION_MINOR >= 7
+		outsize = LZ4_compress_HC_continue(
 		    data->lz4_stream, p, data->out + 4, (int)length,
 		    (int)data->block_size);
-	} else {
+#else
+		outsize = LZ4_compressHC2_limitedOutput_continue(
+		    data->lz4_stream, p, data->out + 4, (int)length,
+		    (int)data->block_size, data->compression_level);
+#endif
+	} else
+#endif
+	{
 		if (data->lz4_stream == NULL) {
-			data->lz4_stream =
-			    LZ4_createHC(data->in_buffer_allocated);
+			data->lz4_stream = LZ4_createStream();
 			if (data->lz4_stream == NULL) {
 				archive_set_error(f->archive, ENOMEM,
 				    "Can't allocate data for compression"
 				    " buffer");
 				return (ARCHIVE_FATAL);
 			}
 		}
-		outsize = LZ4_compressHC2_limitedOutput_continue(
+		else
+			LZ4_loadDict(data->lz4_stream, data->in_buffer_allocated, DICT_SIZE);
+
+#if LZ4_VERSION_MAJOR >= 1 && LZ4_VERSION_MINOR >= 7
+		outsize = LZ4_compress_fast_continue(
 		    data->lz4_stream, p, data->out + 4, (int)length,
-		    (int)data->block_size, data->compression_level);
+		    (int)data->block_size, 1);
+#else
+		outsize = LZ4_compress_limitedOutput_continue(
+		    data->lz4_stream, p, data->out + 4, (int)length,
+		    (int)data->block_size);
+#endif
 	}
 
 	if (outsize) {
@@ -568,14 +624,19 @@ drive_compressor_dependence(struct archive_write_filter *f, const char *p,
 	}
 
 	if (length == data->block_size) {
-#define DICT_SIZE	(64 * 1024)
-		if (data->compression_level < 3)
-			LZ4_saveDict(data->lz4_stream,
-			    data->in_buffer_allocated, DICT_SIZE);
-		else {
+#ifdef HAVE_LZ4HC_H
+		if (data->compression_level >= 3) {
+#if LZ4_VERSION_MAJOR >= 1 && LZ4_VERSION_MINOR >= 7
+			LZ4_saveDictHC(data->lz4_stream, data->in_buffer_allocated, DICT_SIZE);
+#else
 			LZ4_slideInputBufferHC(data->lz4_stream);
+#endif
 			data->in_buffer = data->in_buffer_allocated + DICT_SIZE;
 		}
+		else
+#endif
+			LZ4_saveDict(data->lz4_stream,
+			    data->in_buffer_allocated, DICT_SIZE);
 #undef DICT_SIZE
 	}
 	return (ARCHIVE_OK);
@@ -605,7 +666,7 @@ archive_filter_lz4_open(struct archive_write_filter *f)
 	if (data->block_checksum)
 		archive_strcat(&as, " -BX");
 	if (data->stream_checksum == 0)
-		archive_strcat(&as, " -Sx");
+		archive_strcat(&as, " --no-frame-crc");
 	if (data->block_independence == 0)
 		archive_strcat(&as, " -BD");
 