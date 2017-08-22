@@ -100,6 +100,7 @@ archive_write_add_filter_lzip(struct archive *a)
 
 struct private_data {
 	int		 compression_level;
+	uint32_t	 threads;
 	lzma_stream	 stream;
 	lzma_filter	 lzmafilters[2];
 	lzma_options_lzma lzma_opt;
@@ -151,6 +152,7 @@ common_setup(struct archive_write_filter *f)
 	}
 	f->data = data;
 	data->compression_level = LZMA_PRESET_DEFAULT;
+	data->threads = 1;
 	f->open = &archive_compressor_xz_open;
 	f->close = archive_compressor_xz_close;
 	f->free = archive_compressor_xz_free;
@@ -221,23 +223,37 @@ archive_compressor_xz_init_stream(struct archive_write_filter *f,
 {
 	static const lzma_stream lzma_stream_init_data = LZMA_STREAM_INIT;
 	int ret;
+#ifdef HAVE_LZMA_STREAM_ENCODER_MT
+	lzma_mt mt_options;
+#endif
 
 	data->stream = lzma_stream_init_data;
 	data->stream.next_out = data->compressed;
 	data->stream.avail_out = data->compressed_buffer_size;
-	if (f->code == ARCHIVE_FILTER_XZ)
-		ret = lzma_stream_encoder(&(data->stream),
-		    data->lzmafilters, LZMA_CHECK_CRC64);
-	else if (f->code == ARCHIVE_FILTER_LZMA)
+	if (f->code == ARCHIVE_FILTER_XZ) {
+#ifdef HAVE_LZMA_STREAM_ENCODER_MT
+		if (data->threads != 1) {
+			bzero(&mt_options, sizeof(mt_options));
+			mt_options.threads = data->threads;
+			mt_options.timeout = 300;
+			mt_options.filters = data->lzmafilters;
+			mt_options.check = LZMA_CHECK_CRC64;
+			ret = lzma_stream_encoder_mt(&(data->stream),
+			    &mt_options);
+		} else
+#endif
+			ret = lzma_stream_encoder(&(data->stream),
+			    data->lzmafilters, LZMA_CHECK_CRC64);
+	} else if (f->code == ARCHIVE_FILTER_LZMA) {
 		ret = lzma_alone_encoder(&(data->stream), &data->lzma_opt);
-	else {	/* ARCHIVE_FILTER_LZIP */
+	} else {	/* ARCHIVE_FILTER_LZIP */
 		int dict_size = data->lzma_opt.dict_size;
 		int ds, log2dic, wedges;
 
 		/* Calculate a coded dictionary size */
 		if (dict_size < (1 << 12) || dict_size > (1 << 27)) {
 			archive_set_error(f->archive, ARCHIVE_ERRNO_MISC,
-			    "Unacceptable dictionary dize for lzip: %d",
+			    "Unacceptable dictionary size for lzip: %d",
 			    dict_size);
 			return (ARCHIVE_FATAL);
 		}
@@ -373,6 +389,22 @@ archive_compressor_xz_options(struct archive_write_filter *f,
 		if (data->compression_level > 6)
 			data->compression_level = 6;
 		return (ARCHIVE_OK);
+	} else if (strcmp(key, "threads") == 0) {
+		if (value == NULL)
+			return (ARCHIVE_WARN);
+		data->threads = (int)strtoul(value, NULL, 10);
+		if (data->threads == 0 && errno != 0) {
+			data->threads = 1;
+			return (ARCHIVE_WARN);
+		}
+		if (data->threads == 0) {
+#ifdef HAVE_LZMA_STREAM_ENCODER_MT
+			data->threads = lzma_cputhreads();
+#else
+			data->threads = 1;
+#endif
+		}
+		return (ARCHIVE_OK);
 	}
 
 	/* Note: The "warn" return is just to inform the options