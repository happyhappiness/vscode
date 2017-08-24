@@ -69,7 +69,11 @@ __FBSDID("$FreeBSD$");
 #define _7Z_BZ2		0x040202
 #define _7Z_PPMD	0x030401
 #define _7Z_DELTA	0x03
-#define _7Z_CRYPTO	0x06F10701
+#define _7Z_CRYPTO_MAIN_ZIP			0x06F10101 /* Main Zip crypto algo */
+#define _7Z_CRYPTO_RAR_29			0x06F10303 /* Rar29 AES-128 + (modified SHA-1) */
+#define _7Z_CRYPTO_AES_256_SHA_256	0x06F10701 /* AES-256 + SHA-256 */
+
+
 #define _7Z_X86		0x03030103
 #define _7Z_X86_BCJ2	0x0303011B
 #define _7Z_POWERPC	0x03030205
@@ -322,8 +326,13 @@ struct _7zip {
 	struct archive_string_conv *sconv;
 
 	char			 format_name[64];
+
+	/* Custom value that is non-zero if this archive contains encrypted entries. */
+	int			 has_encrypted_entries;
 };
 
+static int	archive_read_format_7zip_has_encrypted_entries(struct archive_read *);
+static int	archive_read_support_format_7zip_capabilities(struct archive_read *a);
 static int	archive_read_format_7zip_bid(struct archive_read *, int);
 static int	archive_read_format_7zip_cleanup(struct archive_read *);
 static int	archive_read_format_7zip_read_data(struct archive_read *,
@@ -401,6 +410,13 @@ archive_read_support_format_7zip(struct archive *_a)
 		return (ARCHIVE_FATAL);
 	}
 
+	/*
+	 * Until enough data has been read, we cannot tell about
+	 * any encrypted entries yet.
+	 */
+	zip->has_encrypted_entries = ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW;
+
+
 	r = __archive_read_register_format(a,
 	    zip,
 	    "7zip",
@@ -410,14 +426,37 @@ archive_read_support_format_7zip(struct archive *_a)
 	    archive_read_format_7zip_read_data,
 	    archive_read_format_7zip_read_data_skip,
 	    NULL,
-	    archive_read_format_7zip_cleanup);
+	    archive_read_format_7zip_cleanup,
+	    archive_read_support_format_7zip_capabilities,
+	    archive_read_format_7zip_has_encrypted_entries);
 
 	if (r != ARCHIVE_OK)
 		free(zip);
 	return (ARCHIVE_OK);
 }
 
 static int
+archive_read_support_format_7zip_capabilities(struct archive_read * a)
+{
+	(void)a; /* UNUSED */
+	return (ARCHIVE_READ_FORMAT_CAPS_ENCRYPT_DATA |
+			ARCHIVE_READ_FORMAT_CAPS_ENCRYPT_METADATA);
+}
+
+
+static int
+archive_read_format_7zip_has_encrypted_entries(struct archive_read *_a)
+{
+	if (_a && _a->format) {
+		struct _7zip * zip = (struct _7zip *)_a->format->data;
+		if (zip) {
+			return zip->has_encrypted_entries;
+		}
+	}
+	return ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW;
+}
+
+static int
 archive_read_format_7zip_bid(struct archive_read *a, int best_bid)
 {
 	const char *p;
@@ -476,23 +515,23 @@ check_7zip_header_in_sfx(const char *p)
 	switch ((unsigned char)p[5]) {
 	case 0x1C:
 		if (memcmp(p, _7ZIP_SIGNATURE, 6) != 0)
-			return (6); 
+			return (6);
 		/*
 		 * Test the CRC because its extraction code has 7-Zip
 		 * Magic Code, so we should do this in order not to
 		 * make a mis-detection.
 		 */
 		if (crc32(0, (const unsigned char *)p + 12, 20)
 			!= archive_le32dec(p + 8))
-			return (6); 
+			return (6);
 		/* Hit the header! */
 		return (0);
-	case 0x37: return (5); 
-	case 0x7A: return (4); 
-	case 0xBC: return (3); 
-	case 0xAF: return (2); 
-	case 0x27: return (1); 
-	default: return (6); 
+	case 0x37: return (5);
+	case 0x7A: return (4);
+	case 0xBC: return (3);
+	case 0xAF: return (2);
+	case 0x27: return (1);
+	default: return (6);
 	}
 }
 
@@ -568,6 +607,19 @@ archive_read_format_7zip_read_header(struct archive_read *a,
 	struct _7zip *zip = (struct _7zip *)a->format->data;
 	struct _7zip_entry *zip_entry;
 	int r, ret = ARCHIVE_OK;
+	struct _7z_folder *folder = 0;
+	uint64_t fidx = 0;
+
+	/*
+	 * It should be sufficient to call archive_read_next_header() for
+	 * a reader to determine if an entry is encrypted or not. If the
+	 * encryption of an entry is only detectable when calling
+	 * archive_read_data(), so be it. We'll do the same check there
+	 * as well.
+	 */
+	if (zip->has_encrypted_entries == ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW) {
+		zip->has_encrypted_entries = 0;
+	}
 
 	a->archive.archive_format = ARCHIVE_FORMAT_7ZIP;
 	if (a->archive.archive_format_name == NULL)
@@ -604,6 +656,32 @@ archive_read_format_7zip_read_header(struct archive_read *a,
 			return (ARCHIVE_FATAL);
 	}
 
+	/* Figure out if the entry is encrypted by looking at the folder
+	   that is associated to the current 7zip entry. If the folder
+	   has a coder with a _7Z_CRYPTO codec then the folder is encrypted.
+	   Hence the entry must also be encrypted. */
+	if (zip_entry && zip_entry->folderIndex < zip->si.ci.numFolders) {
+		folder = &(zip->si.ci.folders[zip_entry->folderIndex]);
+		for (fidx=0; folder && fidx<folder->numCoders; fidx++) {
+			switch(folder->coders[fidx].codec) {
+				case _7Z_CRYPTO_MAIN_ZIP:
+				case _7Z_CRYPTO_RAR_29:
+				case _7Z_CRYPTO_AES_256_SHA_256: {
+					archive_entry_set_is_data_encrypted(entry, 1);
+					zip->has_encrypted_entries = 1;
+					break;
+				}
+			}
+		}
+	}
+
+	/* Now that we've checked for encryption, if there were still no
+	 * encrypted entries found we can say for sure that there are none.
+	 */
+	if (zip->has_encrypted_entries == ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW) {
+		zip->has_encrypted_entries = 0;
+	}
+
 	if (archive_entry_copy_pathname_l(entry,
 	    (const char *)zip_entry->utf16name,
 	    zip_entry->name_len, zip->sconv) != 0) {
@@ -707,6 +785,10 @@ archive_read_format_7zip_read_data(struct archive_read *a,
 
 	zip = (struct _7zip *)(a->format->data);
 
+	if (zip->has_encrypted_entries == ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW) {
+		zip->has_encrypted_entries = 0;
+	}
+
 	if (zip->pack_stream_bytes_unconsumed)
 		read_consume(a);
 
@@ -969,7 +1051,7 @@ init_decompression(struct archive_read *a, struct _7zip *zip,
 	{
 		lzma_options_delta delta_opt;
 		lzma_filter filters[LZMA_FILTERS_MAX];
-#if LZMA_VERSION < 50000030
+#if LZMA_VERSION < 50010000
 		lzma_filter *ff;
 #endif
 		int fi = 0;
@@ -994,7 +1076,7 @@ init_decompression(struct archive_read *a, struct _7zip *zip,
 		 * for BCJ+LZMA. If we were able to tell the uncompressed
 		 * size to liblzma when using lzma_raw_decoder() liblzma
 		 * could correctly deal with BCJ+LZMA. But unfortunately
-		 * there is no way to do that. 
+		 * there is no way to do that.
 		 * Discussion about this can be found at XZ Utils forum.
 		 */
 		if (coder2 != NULL) {
@@ -1056,7 +1138,7 @@ init_decompression(struct archive_read *a, struct _7zip *zip,
 		else
 			filters[fi].id = LZMA_FILTER_LZMA1;
 		filters[fi].options = NULL;
-#if LZMA_VERSION < 50000030
+#if LZMA_VERSION < 50010000
 		ff = &filters[fi];
 #endif
 		r = lzma_properties_decode(&filters[fi], NULL,
@@ -1070,7 +1152,7 @@ init_decompression(struct archive_read *a, struct _7zip *zip,
 		filters[fi].id = LZMA_VLI_UNKNOWN;
 		filters[fi].options = NULL;
 		r = lzma_raw_decoder(&(zip->lzstream), filters);
-#if LZMA_VERSION < 50000030
+#if LZMA_VERSION < 50010000
 		free(ff->options);
 #endif
 		if (r != LZMA_OK) {
@@ -1203,6 +1285,17 @@ init_decompression(struct archive_read *a, struct _7zip *zip,
 		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
 		    "Unexpected codec ID: %lX", zip->codec);
 		return (ARCHIVE_FAILED);
+	case _7Z_CRYPTO_MAIN_ZIP:
+	case _7Z_CRYPTO_RAR_29:
+	case _7Z_CRYPTO_AES_256_SHA_256:
+		if (a->entry) {
+			archive_entry_set_is_metadata_encrypted(a->entry, 1);
+			archive_entry_set_is_data_encrypted(a->entry, 1);
+			zip->has_encrypted_entries = 1;
+		}
+		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+		    "Crypto codec not supported yet (ID: 0x%lX)", zip->codec);
+		return (ARCHIVE_FAILED);
 	default:
 		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
 		    "Unknown codec ID: %lX", zip->codec);
@@ -1426,7 +1519,7 @@ decompress(struct archive_read *a, struct _7zip *zip,
 
 		do {
 			int sym;
-			
+
 			sym = __archive_ppmd7_functions.Ppmd7_DecodeSymbol(
 				&(zip->ppmd7_context), &(zip->range_dec.p));
 			if (sym < 0) {
@@ -2755,6 +2848,7 @@ slurp_central_directory(struct archive_read *a, struct _7zip *zip,
 	zip->header_crc32 = 0;
 	zip->header_is_encoded = 0;
 	zip->header_is_being_read = 1;
+	zip->has_encrypted_entries = 0;
 	check_header_crc = 1;
 
 	if ((p = header_bytes(a, 1)) == NULL) {
@@ -3170,7 +3264,7 @@ read_stream(struct archive_read *a, const void **buff, size_t size,
 		return (r);
 
 	/*
-	 * Skip the bytes we alrady has skipped in skip_stream(). 
+	 * Skip the bytes we alrady has skipped in skip_stream().
 	 */
 	while (skip_bytes) {
 		ssize_t skipped;
@@ -3235,16 +3329,36 @@ setup_decode_folder(struct archive_read *a, struct _7z_folder *folder,
 	 * Check coder types.
 	 */
 	for (i = 0; i < folder->numCoders; i++) {
-		if (folder->coders[i].codec == _7Z_CRYPTO) {
-			archive_set_error(&(a->archive),
-			    ARCHIVE_ERRNO_MISC,
-			    "The %s is encrypted, "
-			    "but currently not supported", cname);
-			return (ARCHIVE_FATAL);
+		switch(folder->coders[i].codec) {
+			case _7Z_CRYPTO_MAIN_ZIP:
+			case _7Z_CRYPTO_RAR_29:
+			case _7Z_CRYPTO_AES_256_SHA_256: {
+				/* For entry that is associated with this folder, mark
+				   it as encrypted (data+metadata). */
+				zip->has_encrypted_entries = 1;
+				if (a->entry) {
+					archive_entry_set_is_data_encrypted(a->entry, 1);
+					archive_entry_set_is_metadata_encrypted(a->entry, 1);
+				}
+				archive_set_error(&(a->archive),
+					ARCHIVE_ERRNO_MISC,
+					"The %s is encrypted, "
+					"but currently not supported", cname);
+				return (ARCHIVE_FATAL);
+			}
+			case _7Z_X86_BCJ2: {
+				found_bcj2++;
+				break;
+			}
 		}
-		if (folder->coders[i].codec == _7Z_X86_BCJ2)
-			found_bcj2++;
 	}
+	/* Now that we've checked for encryption, if there were still no
+	 * encrypted entries found we can say for sure that there are none.
+	 */
+	if (zip->has_encrypted_entries == ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW) {
+		zip->has_encrypted_entries = 0;
+	}
+
 	if ((folder->numCoders > 2 && !found_bcj2) || found_bcj2 > 1) {
 		archive_set_error(&(a->archive),
 		    ARCHIVE_ERRNO_MISC,