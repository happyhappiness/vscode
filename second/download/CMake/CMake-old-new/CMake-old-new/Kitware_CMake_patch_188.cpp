@@ -1,6 +1,6 @@
 /*-
  * Copyright (c) 2004-2013 Tim Kientzle
- * Copyright (c) 2011-2012 Michihiro NAKAJIMA
+ * Copyright (c) 2011-2012,2014 Michihiro NAKAJIMA
  * Copyright (c) 2013 Konrad Kleine
  * All rights reserved.
  *
@@ -53,9 +53,12 @@ __FBSDID("$FreeBSD: head/lib/libarchive/archive_read_support_format_zip.c 201102
 #endif
 
 #include "archive.h"
+#include "archive_digest_private.h"
+#include "archive_cryptor_private.h"
 #include "archive_endian.h"
 #include "archive_entry.h"
 #include "archive_entry_locale.h"
+#include "archive_hmac_private.h"
 #include "archive_private.h"
 #include "archive_rb.h"
 #include "archive_read_private.h"
@@ -86,6 +89,25 @@ struct zip_entry {
 	unsigned char		compression;
 	unsigned char		system; /* From "version written by" */
 	unsigned char		flags; /* Our extra markers. */
+	unsigned char		decdat;/* Used for Decryption check */
+
+	/* WinZip AES encryption extra field should be available
+	 * when compression is 99. */
+	struct {
+		/* Vendor version: AE-1 - 0x0001, AE-2 - 0x0002 */
+		unsigned	vendor;
+#define AES_VENDOR_AE_1	0x0001
+#define AES_VENDOR_AE_2	0x0002
+		/* AES encryption strength:
+		 * 1 - 128 bits, 2 - 192 bits, 2 - 256 bits. */
+		unsigned	strength;
+		/* Actual compression method. */
+		unsigned char	compression;
+	}			aes_extra;
+};
+
+struct trad_enc_ctx {
+	uint32_t	keys[3];
 };
 
 /* Bits used in zip_flags. */
@@ -101,9 +123,20 @@ struct zip_entry {
 #define LA_USED_ZIP64	(1 << 0)
 #define LA_FROM_CENTRAL_DIRECTORY (1 << 1)
 
+/*
+ * See "WinZip - AES Encryption Information"
+ *     http://www.winzip.com/aes_info.htm
+ */
+/* Value used in compression method. */
+#define WINZIP_AES_ENCRYPTION	99
+/* Authentication code size. */
+#define AUTH_CODE_SIZE	10
+/**/
+#define MAX_DERIVED_KEY_BUF_SIZE	(AES_MAX_KEY_SIZE * 2 + 2)
+
 struct zip {
 	/* Structural information about the archive. */
-	char			format_name[64];
+	struct archive_string	format_name;
 	int64_t			central_directory_offset;
 	size_t			central_directory_entries_total;
 	size_t			central_directory_entries_on_this_disk;
@@ -127,7 +160,8 @@ struct zip {
 
 	/* Running CRC32 of the decompressed data */
 	unsigned long		entry_crc32;
-	unsigned long		(*crc32func)(unsigned long, const void *, size_t);
+	unsigned long		(*crc32func)(unsigned long, const void *,
+				    size_t);
 	char			ignore_crc32;
 
 	/* Flags to mark progress of decompression. */
@@ -146,6 +180,38 @@ struct zip {
 	struct archive_string_conv *sconv_utf8;
 	int			init_default_conversion;
 	int			process_mac_extensions;
+
+	char			init_decryption;
+
+	/* Decryption buffer. */
+	unsigned char 		*decrypted_buffer;
+	unsigned char 		*decrypted_ptr;
+	size_t 			decrypted_buffer_size;
+	size_t 			decrypted_bytes_remaining;
+	size_t 			decrypted_unconsumed_bytes;
+
+	/* Traditional PKWARE decryption. */
+	struct trad_enc_ctx	tctx;
+	char			tctx_valid;
+
+	/* WinZip AES decyption. */
+	/* Contexts used for AES decryption. */
+	archive_crypto_ctx	cctx;
+	char			cctx_valid;
+	archive_hmac_sha1_ctx	hctx;
+	char			hctx_valid;
+
+	/* Strong encryption's decryption header information. */
+	unsigned		iv_size;
+	unsigned		alg_id;
+	unsigned		bit_len;
+	unsigned		flags;
+	unsigned		erd_size;
+	unsigned		v_size;
+	unsigned		v_crc32;
+	uint8_t			*iv;
+	uint8_t			*erd;
+	uint8_t			*v_data;
 };
 
 /* Many systems define min or MIN, but not all. */
@@ -154,6 +220,106 @@ struct zip {
 /* ------------------------------------------------------------------------ */
 
 /*
+  Traditional PKWARE Decryption functions.
+ */
+
+static void
+trad_enc_update_keys(struct trad_enc_ctx *ctx, uint8_t c)
+{
+	uint8_t t;
+#define CRC32(c, b) (crc32(c ^ 0xffffffffUL, &b, 1) ^ 0xffffffffUL)
+
+	ctx->keys[0] = CRC32(ctx->keys[0], c);
+	ctx->keys[1] = (ctx->keys[1] + (ctx->keys[0] & 0xff)) * 134775813L + 1;
+	t = (ctx->keys[1] >> 24) & 0xff;
+	ctx->keys[2] = CRC32(ctx->keys[2], t);
+#undef CRC32
+}
+
+static uint8_t
+trad_enc_decypt_byte(struct trad_enc_ctx *ctx)
+{
+	unsigned temp = ctx->keys[2] | 2;
+	return (uint8_t)((temp * (temp ^ 1)) >> 8) & 0xff;
+}
+
+static void
+trad_enc_decrypt_update(struct trad_enc_ctx *ctx, const uint8_t *in,
+    size_t in_len, uint8_t *out, size_t out_len)
+{
+	unsigned i, max;
+
+	max = (unsigned)((in_len < out_len)? in_len: out_len);
+
+	for (i = 0; i < max; i++) {
+		uint8_t t = in[i] ^ trad_enc_decypt_byte(ctx);
+		out[i] = t;
+		trad_enc_update_keys(ctx, t);
+	}
+}
+
+static int
+trad_enc_init(struct trad_enc_ctx *ctx, const char *pw, size_t pw_len,
+    const uint8_t *key, size_t key_len, uint8_t *crcchk)
+{
+	uint8_t header[12];
+
+	if (key_len < 12) {
+		*crcchk = 0xff;
+		return -1;
+	}
+
+	ctx->keys[0] = 305419896L;
+	ctx->keys[1] = 591751049L;
+	ctx->keys[2] = 878082192L;
+
+	for (;pw_len; --pw_len)
+		trad_enc_update_keys(ctx, *pw++);
+
+	trad_enc_decrypt_update(ctx, key, 12, header, 12);
+	/* Return the last byte for CRC check. */
+	*crcchk = header[11];
+	return 0;
+}
+
+#if 0
+static void
+crypt_derive_key_sha1(const void *p, int size, unsigned char *key,
+    int key_size)
+{
+#define MD_SIZE 20
+	archive_sha1_ctx ctx;
+	unsigned char md1[MD_SIZE];
+	unsigned char md2[MD_SIZE * 2];
+	unsigned char mkb[64];
+	int i;
+
+	archive_sha1_init(&ctx);
+	archive_sha1_update(&ctx, p, size);
+	archive_sha1_final(&ctx, md1);
+
+	memset(mkb, 0x36, sizeof(mkb));
+	for (i = 0; i < MD_SIZE; i++)
+		mkb[i] ^= md1[i];
+	archive_sha1_init(&ctx);
+	archive_sha1_update(&ctx, mkb, sizeof(mkb));
+	archive_sha1_final(&ctx, md2);
+
+	memset(mkb, 0x5C, sizeof(mkb));
+	for (i = 0; i < MD_SIZE; i++)
+		mkb[i] ^= md1[i];
+	archive_sha1_init(&ctx);
+	archive_sha1_update(&ctx, mkb, sizeof(mkb));
+	archive_sha1_final(&ctx, md2 + MD_SIZE);
+
+	if (key_size > 32)
+		key_size = 32;
+	memcpy(key, md2, key_size);
+#undef MD_SIZE
+}
+#endif
+
+/*
  * Common code for streaming or seeking modes.
  *
  * Includes code to read local file headers, decompress data
@@ -163,9 +329,10 @@ struct zip {
 static unsigned long
 real_crc32(unsigned long crc, const void *buff, size_t len)
 {
-	return crc32(crc, buff, len);
+	return crc32(crc, buff, (unsigned int)len);
 }
 
+/* Used by "ignorecrc32" option to speed up tests. */
 static unsigned long
 fake_crc32(unsigned long crc, const void *buff, size_t len)
 {
@@ -185,33 +352,36 @@ static struct {
 	{3, "reduced-2"}, /* The file is Reduced with compression factor 2 */
 	{4, "reduced-3"}, /* The file is Reduced with compression factor 3 */
 	{5, "reduced-4"}, /* The file is Reduced with compression factor 4 */
-	{6, "imploded"}, /* The file is Imploded */
-	{7, "reserved"}, /* Reserved for Tokenizing compression algorithm */
+	{6, "imploded"},  /* The file is Imploded */
+	{7, "reserved"},  /* Reserved for Tokenizing compression algorithm */
 	{8, "deflation"}, /* The file is Deflated */
 	{9, "deflation-64-bit"}, /* Enhanced Deflating using Deflate64(tm) */
-	{10, "ibm-terse"}, /* PKWARE Data Compression Library Imploding (old IBM TERSE) */
+	{10, "ibm-terse"},/* PKWARE Data Compression Library Imploding
+			   * (old IBM TERSE) */
 	{11, "reserved"}, /* Reserved by PKWARE */
-	{12, "bzip"}, /* File is compressed using BZIP2 algorithm */
+	{12, "bzip"},     /* File is compressed using BZIP2 algorithm */
 	{13, "reserved"}, /* Reserved by PKWARE */
-	{14, "lzma"}, /* LZMA (EFS) */
+	{14, "lzma"},     /* LZMA (EFS) */
 	{15, "reserved"}, /* Reserved by PKWARE */
 	{16, "reserved"}, /* Reserved by PKWARE */
 	{17, "reserved"}, /* Reserved by PKWARE */
 	{18, "ibm-terse-new"}, /* File is compressed using IBM TERSE (new) */
-	{19, "ibm-lz777"}, /* IBM LZ77 z Architecture (PFS) */
+	{19, "ibm-lz777"},/* IBM LZ77 z Architecture (PFS) */
 	{97, "wav-pack"}, /* WavPack compressed data */
-	{98, "ppmd-1"} /* PPMd version I, Rev 1 */
+	{98, "ppmd-1"},   /* PPMd version I, Rev 1 */
+	{99, "aes"}       /* WinZip AES encryption  */
 };
 
 static const char *
 compression_name(const int compression)
 {
-	static const int num_compression_methods = sizeof(compression_methods)/sizeof(compression_methods[0]);
+	static const int num_compression_methods =
+		sizeof(compression_methods)/sizeof(compression_methods[0]);
 	int i=0;
+
 	while(compression >= 0 && i < num_compression_methods) {
-		if (compression_methods[i].id == compression) {
+		if (compression_methods[i].id == compression)
 			return compression_methods[i].name;
-		}
 		i++;
 	}
 	return "??";
@@ -248,15 +418,15 @@ process_extra(const char *p, size_t extra_length, struct zip_entry* zip_entry)
 {
 	unsigned offset = 0;
 
-	while (offset < extra_length - 4)
-	{
+	while (offset < extra_length - 4) {
 		unsigned short headerid = archive_le16dec(p + offset);
 		unsigned short datasize = archive_le16dec(p + offset + 2);
+
 		offset += 4;
 		if (offset + datasize > extra_length)
 			break;
 #ifdef DEBUG
-		fprintf(stderr, "Header id 0x%x, length %d\n",
+		fprintf(stderr, "Header id 0x%04x, length %d\n",
 		    headerid, datasize);
 #endif
 		switch (headerid) {
@@ -291,6 +461,23 @@ process_extra(const char *p, size_t extra_length, struct zip_entry* zip_entry)
 			 * on which file starts, but we don't handle
 			 * multi-volume Zip files. */
 			break;
+#ifdef DEBUG
+		case 0x0017:
+		{
+			/* Strong encryption field. */
+			if (archive_le16dec(p + offset) == 2) {
+				unsigned algId =
+					archive_le16dec(p + offset + 2);
+				unsigned bitLen =
+					archive_le16dec(p + offset + 4);
+				int	 flags =
+					archive_le16dec(p + offset + 6);
+				fprintf(stderr, "algId=0x%04x, bitLen=%u, "
+				    "flgas=%d\n", algId, bitLen,flags);
+			}
+			break;
+		}
+#endif
 		case 0x5455:
 		{
 			/* Extended time field "UT". */
@@ -345,16 +532,34 @@ process_extra(const char *p, size_t extra_length, struct zip_entry* zip_entry)
 			}
 			break;
 		}
-		case 0x6c65:
+		case 0x6c78:
 		{
-			/* Experimental 'el' field */
+			/* Experimental 'xl' field */
 			/*
 			 * Introduced Dec 2013 to provide a way to
-			 * include external file attributes in local file
-			 * header.  This provides file type and permission
-			 * information necessary to support full streaming
-			 * extraction.  Currently being discussed with
-			 * other Zip developers... subject to change.
+			 * include external file attributes (and other
+			 * fields that ordinarily appear only in
+			 * central directory) in local file header.
+			 * This provides file type and permission
+			 * information necessary to support full
+			 * streaming extraction.  Currently being
+			 * discussed with other Zip developers
+			 * ... subject to change.
+			 *
+			 * Format:
+			 *  The field starts with a bitmap that specifies
+			 *  which additional fields are included.  The
+			 *  bitmap is variable length and can be extended in
+			 *  the future.
+			 *
+			 *  n bytes - feature bitmap: first byte has low-order
+			 *    7 bits.  If high-order bit is set, a subsequent
+			 *    byte holds the next 7 bits, etc.
+			 *
+			 *  if bitmap & 1, 2 byte "version made by"
+			 *  if bitmap & 2, 2 byte "internal file attributes"
+			 *  if bitmap & 4, 4 byte "external file attributes"
+			 *  if bitmap * 7, 2 byte comment length + n byte comment
 			 */
 			int bitmap, bitmap_last;
 
@@ -373,7 +578,7 @@ process_extra(const char *p, size_t extra_length, struct zip_entry* zip_entry)
 			}
 
 			if (bitmap & 1) {
-				// 2 byte "version made by"
+				/* 2 byte "version made by" */
 				if (datasize < 2)
 					break;
 				zip_entry->system
@@ -382,19 +587,19 @@ process_extra(const char *p, size_t extra_length, struct zip_entry* zip_entry)
 				datasize -= 2;
 			}
 			if (bitmap & 2) {
-				// 2 byte "internal file attributes"
+				/* 2 byte "internal file attributes" */
 				uint32_t internal_attributes;
 				if (datasize < 2)
 					break;
 				internal_attributes
 				    = archive_le16dec(p + offset);
-				// Not used by libarchive at present.
+				/* Not used by libarchive at present. */
 				(void)internal_attributes; /* UNUSED */
 				offset += 2;
 				datasize -= 2;
 			}
 			if (bitmap & 4) {
-				// 4 byte "external file attributes"
+				/* 4 byte "external file attributes" */
 				uint32_t external_attributes;
 				if (datasize < 4)
 					break;
@@ -408,7 +613,7 @@ process_extra(const char *p, size_t extra_length, struct zip_entry* zip_entry)
 				datasize -= 4;
 			}
 			if (bitmap & 8) {
-				// 2 byte comment length + comment
+				/* 2 byte comment length + comment */
 				uint32_t comment_length;
 				if (datasize < 2)
 					break;
@@ -419,7 +624,7 @@ process_extra(const char *p, size_t extra_length, struct zip_entry* zip_entry)
 
 				if (datasize < comment_length)
 					break;
-				// Comment is not supported by libarchive
+				/* Comment is not supported by libarchive */
 				offset += comment_length;
 				datasize -= comment_length;
 			}
@@ -447,7 +652,7 @@ process_extra(const char *p, size_t extra_length, struct zip_entry* zip_entry)
 			if (datasize >= 1 && p[offset] == 1) {/* version=1 */
 				if (datasize >= 4) {
 					/* get a uid size. */
-					uidsize = p[offset+1];
+					uidsize = 0xff & (int)p[offset+1];
 					if (uidsize == 2)
 						zip_entry->uid =
 						    archive_le16dec(
@@ -459,7 +664,7 @@ process_extra(const char *p, size_t extra_length, struct zip_entry* zip_entry)
 				}
 				if (datasize >= (2 + uidsize + 3)) {
 					/* get a gid size. */
-					gidsize = p[offset+2+uidsize];
+					gidsize = 0xff & (int)p[offset+2+uidsize];
 					if (gidsize == 2)
 						zip_entry->gid =
 						    archive_le16dec(
@@ -473,6 +678,19 @@ process_extra(const char *p, size_t extra_length, struct zip_entry* zip_entry)
 			}
 			break;
 		}
+		case 0x9901:
+			/* WinZIp AES extra data field. */
+			if (p[offset + 2] == 'A' && p[offset + 3] == 'E') {
+				/* Vendor version. */
+				zip_entry->aes_extra.vendor =
+				    archive_le16dec(p + offset);
+				/* AES encryption strength. */
+				zip_entry->aes_extra.strength = p[offset + 4];
+				/* Actual compression method. */
+				zip_entry->aes_extra.compression =
+				    p[offset + 5];
+			}
+			break;
 		default:
 			break;
 		}
@@ -544,9 +762,14 @@ zip_read_local_file_header(struct archive_read *a, struct archive_entry *entry,
 			return ARCHIVE_FATAL;
 		}
 	}
+	zip->init_decryption = (zip_entry->zip_flags & ZIP_ENCRYPTED);
 	zip_entry->compression = (char)archive_le16dec(p + 8);
 	zip_entry->mtime = zip_time(p + 10);
 	zip_entry->crc32 = archive_le32dec(p + 14);
+	if (zip_entry->zip_flags & ZIP_LENGTH_AT_END)
+		zip_entry->decdat = p[11];
+	else
+		zip_entry->decdat = p[17];
 	zip_entry->compressed_size = archive_le32dec(p + 18);
 	zip_entry->uncompressed_size = archive_le32dec(p + 22);
 	filename_length = archive_le16dec(p + 26);
@@ -687,7 +910,15 @@ zip_read_local_file_header(struct archive_read *a, struct archive_entry *entry,
 	archive_entry_set_atime(entry, zip_entry->atime, 0);
 
 	if ((zip->entry->mode & AE_IFMT) == AE_IFLNK) {
-		size_t linkname_length = zip_entry->compressed_size;
+		size_t linkname_length;
+
+		if (zip_entry->compressed_size > 64 * 1024) {
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+			    "Zip file with oversized link entry");
+			return ARCHIVE_FATAL;
+		}
+
+		linkname_length = (size_t)zip_entry->compressed_size;
 
 		archive_entry_set_size(entry, 0);
 		p = __archive_read_ahead(a, linkname_length, NULL);
@@ -696,11 +927,6 @@ zip_read_local_file_header(struct archive_read *a, struct archive_entry *entry,
 			    "Truncated Zip file");
 			return ARCHIVE_FATAL;
 		}
-		if (__archive_read_consume(a, linkname_length) < 0) {
-			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
-			    "Read error skipping symlink target name");
-			return ARCHIVE_FATAL;
-		}
 
 		sconv = zip->sconv;
 		if (sconv == NULL && (zip->entry->zip_flags & ZIP_UTF8_NAME))
@@ -735,6 +961,12 @@ zip_read_local_file_header(struct archive_read *a, struct archive_entry *entry,
 			}
 		}
 		zip_entry->uncompressed_size = zip_entry->compressed_size = 0;
+
+		if (__archive_read_consume(a, linkname_length) < 0) {
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+			    "Read error skipping symlink target name");
+			return ARCHIVE_FATAL;
+		}
 	} else if (0 == (zip_entry->zip_flags & ZIP_LENGTH_AT_END)
 	    || zip_entry->uncompressed_size > 0) {
 		/* Set the size only if it's meaningful. */
@@ -748,14 +980,51 @@ zip_read_local_file_header(struct archive_read *a, struct archive_entry *entry,
 		zip->end_of_entry = 1;
 
 	/* Set up a more descriptive format name. */
-	snprintf(zip->format_name, sizeof(zip->format_name), "ZIP %d.%d (%s)",
+	archive_string_sprintf(&zip->format_name, "ZIP %d.%d (%s)",
 	    version / 10, version % 10,
 	    compression_name(zip->entry->compression));
-	a->archive.archive_format_name = zip->format_name;
+	a->archive.archive_format_name = zip->format_name.s;
 
 	return (ret);
 }
 
+static int
+check_authentication_code(struct archive_read *a, const void *_p)
+{
+	struct zip *zip = (struct zip *)(a->format->data);
+
+	/* Check authentication code. */
+	if (zip->hctx_valid) {
+		const void *p;
+		uint8_t hmac[20];
+		size_t hmac_len = 20;
+		int cmp;
+
+		archive_hmac_sha1_final(&zip->hctx, hmac, &hmac_len);
+		if (_p == NULL) {
+			/* Read authentication code. */
+			p = __archive_read_ahead(a, AUTH_CODE_SIZE, NULL);
+			if (p == NULL) {
+				archive_set_error(&a->archive,
+				    ARCHIVE_ERRNO_FILE_FORMAT,
+				    "Truncated ZIP file data");
+				return (ARCHIVE_FATAL);
+			}
+		} else {
+			p = _p;
+		}
+		cmp = memcmp(hmac, p, AUTH_CODE_SIZE);
+		__archive_read_consume(a, AUTH_CODE_SIZE);
+		if (cmp != 0) {
+			archive_set_error(&a->archive,
+			    ARCHIVE_ERRNO_MISC,
+			    "ZIP bad Authentication code");
+			return (ARCHIVE_WARN);
+		}
+	}
+	return (ARCHIVE_OK);
+}
+
 /*
  * Read "uncompressed" data.  There are three cases:
  *  1) We know the size of the data.  This is always true for the
@@ -787,17 +1056,21 @@ zip_read_data_none(struct archive_read *a, const void **_buff,
 	struct zip *zip;
 	const char *buff;
 	ssize_t bytes_avail;
+	int r;
 
 	(void)offset; /* UNUSED */
 
 	zip = (struct zip *)(a->format->data);
 
 	if (zip->entry->zip_flags & ZIP_LENGTH_AT_END) {
 		const char *p;
+		ssize_t grabbing_bytes = 24;
 
+		if (zip->hctx_valid)
+			grabbing_bytes += AUTH_CODE_SIZE;
 		/* Grab at least 24 bytes. */
-		buff = __archive_read_ahead(a, 24, &bytes_avail);
-		if (bytes_avail < 24) {
+		buff = __archive_read_ahead(a, grabbing_bytes, &bytes_avail);
+		if (bytes_avail < grabbing_bytes) {
 			/* Zip archives have end-of-archive markers
 			   that are longer than this, so a failure to get at
 			   least 24 bytes really does indicate a truncated
@@ -810,21 +1083,34 @@ zip_read_data_none(struct archive_read *a, const void **_buff,
 		/* Check for a complete PK\007\010 signature, followed
 		 * by the correct 4-byte CRC. */
 		p = buff;
+		if (zip->hctx_valid)
+			p += AUTH_CODE_SIZE;
 		if (p[0] == 'P' && p[1] == 'K'
 		    && p[2] == '\007' && p[3] == '\010'
 		    && (archive_le32dec(p + 4) == zip->entry_crc32
-			|| zip->ignore_crc32)) {
+			|| zip->ignore_crc32
+			|| (zip->hctx_valid
+			 && zip->entry->aes_extra.vendor == AES_VENDOR_AE_2))) {
 			if (zip->entry->flags & LA_USED_ZIP64) {
 				zip->entry->crc32 = archive_le32dec(p + 4);
-				zip->entry->compressed_size = archive_le64dec(p + 8);
-				zip->entry->uncompressed_size = archive_le64dec(p + 16);
+				zip->entry->compressed_size =
+					archive_le64dec(p + 8);
+				zip->entry->uncompressed_size =
+					archive_le64dec(p + 16);
 				zip->unconsumed = 24;
 			} else {
 				zip->entry->crc32 = archive_le32dec(p + 4);
-				zip->entry->compressed_size = archive_le32dec(p + 8);
-				zip->entry->uncompressed_size = archive_le32dec(p + 12);
+				zip->entry->compressed_size =
+					archive_le32dec(p + 8);
+				zip->entry->uncompressed_size =
+					archive_le32dec(p + 12);
 				zip->unconsumed = 16;
 			}
+			if (zip->hctx_valid) {
+				r = check_authentication_code(a, buff);
+				if (r != ARCHIVE_OK)
+					return (r);
+			}
 			zip->end_of_entry = 1;
 			return (ARCHIVE_OK);
 		}
@@ -841,13 +1127,20 @@ zip_read_data_none(struct archive_read *a, const void **_buff,
 			else if (p[3] == '\007') { p += 1; }
 			else if (p[3] == '\010' && p[2] == '\007'
 			    && p[1] == 'K' && p[0] == 'P') {
+				if (zip->hctx_valid)
+					p -= AUTH_CODE_SIZE;
 				break;
 			} else { p += 4; }
 		}
 		bytes_avail = p - buff;
 	} else {
 		if (zip->entry_bytes_remaining == 0) {
 			zip->end_of_entry = 1;
+			if (zip->hctx_valid) {
+				r = check_authentication_code(a, NULL);
+				if (r != ARCHIVE_OK)
+					return (r);
+			}
 			return (ARCHIVE_OK);
 		}
 		/* Grab a bunch of bytes. */
@@ -861,6 +1154,26 @@ zip_read_data_none(struct archive_read *a, const void **_buff,
 		if (bytes_avail > zip->entry_bytes_remaining)
 			bytes_avail = (ssize_t)zip->entry_bytes_remaining;
 	}
+	if (zip->tctx_valid || zip->cctx_valid) {
+		size_t dec_size = bytes_avail;
+
+		if (dec_size > zip->decrypted_buffer_size)
+			dec_size = zip->decrypted_buffer_size;
+		if (zip->tctx_valid) {
+			trad_enc_decrypt_update(&zip->tctx,
+			    (const uint8_t *)buff, dec_size,
+			    zip->decrypted_buffer, dec_size);
+		} else {
+			size_t dsize = dec_size;
+			archive_hmac_sha1_update(&zip->hctx,
+			    (const uint8_t *)buff, dec_size);
+			archive_decrypto_aes_ctr_update(&zip->cctx,
+			    (const uint8_t *)buff, dec_size,
+			    zip->decrypted_buffer, &dsize);
+		}
+		bytes_avail = dec_size;
+		buff = (const char *)zip->decrypted_buffer;
+	}
 	*size = bytes_avail;
 	zip->entry_bytes_remaining -= bytes_avail;
 	zip->entry_uncompressed_bytes_read += bytes_avail;
@@ -902,7 +1215,7 @@ zip_read_data_deflate(struct archive_read *a, const void **buff,
 {
 	struct zip *zip;
 	ssize_t bytes_avail;
-	const void *compressed_buff;
+	const void *compressed_buff, *sp;
 	int r;
 
 	(void)offset; /* UNUSED */
@@ -931,7 +1244,7 @@ zip_read_data_deflate(struct archive_read *a, const void **buff,
 	 * available bytes; asking for more than that forces the
 	 * decompressor to combine reads by copying data.
 	 */
-	compressed_buff = __archive_read_ahead(a, 1, &bytes_avail);
+	compressed_buff = sp = __archive_read_ahead(a, 1, &bytes_avail);
 	if (0 == (zip->entry->zip_flags & ZIP_LENGTH_AT_END)
 	    && bytes_avail > zip->entry_bytes_remaining) {
 		bytes_avail = (ssize_t)zip->entry_bytes_remaining;
@@ -942,6 +1255,51 @@ zip_read_data_deflate(struct archive_read *a, const void **buff,
 		return (ARCHIVE_FATAL);
 	}
 
+	if (zip->tctx_valid || zip->cctx_valid) {
+		if (zip->decrypted_bytes_remaining < (size_t)bytes_avail) {
+			size_t buff_remaining = zip->decrypted_buffer_size
+			    - (zip->decrypted_ptr - zip->decrypted_buffer);
+
+			if (buff_remaining > (size_t)bytes_avail)
+				buff_remaining = (size_t)bytes_avail;
+
+			if (0 == (zip->entry->zip_flags & ZIP_LENGTH_AT_END) &&
+			      zip->entry_bytes_remaining > 0) {
+				if ((int64_t)(zip->decrypted_bytes_remaining
+				    + buff_remaining)
+				      > zip->entry_bytes_remaining) {
+					if (zip->entry_bytes_remaining <
+					      (int64_t)zip->decrypted_bytes_remaining)
+						buff_remaining = 0;
+					else
+						buff_remaining =
+						    (size_t)zip->entry_bytes_remaining
+						      - zip->decrypted_bytes_remaining;
+				}
+			}
+			if (buff_remaining > 0) {
+				if (zip->tctx_valid) {
+					trad_enc_decrypt_update(&zip->tctx,
+					    compressed_buff, buff_remaining,
+					    zip->decrypted_ptr
+					      + zip->decrypted_bytes_remaining,
+					    buff_remaining);
+				} else {
+					size_t dsize = buff_remaining;
+					archive_decrypto_aes_ctr_update(
+					    &zip->cctx,
+					    compressed_buff, buff_remaining,
+					    zip->decrypted_ptr
+					      + zip->decrypted_bytes_remaining,
+					    &dsize);
+				}
+				zip->decrypted_bytes_remaining += buff_remaining;
+			}
+		}
+		bytes_avail = zip->decrypted_bytes_remaining;
+		compressed_buff = (const char *)zip->decrypted_ptr;
+	}
+
 	/*
 	 * A bug in zlib.h: stream.next_in should be marked 'const'
 	 * but isn't (the library never alters data through the
@@ -974,6 +1332,16 @@ zip_read_data_deflate(struct archive_read *a, const void **buff,
 
 	/* Consume as much as the compressor actually used. */
 	bytes_avail = zip->stream.total_in;
+	if (zip->tctx_valid || zip->cctx_valid) {
+		zip->decrypted_bytes_remaining -= bytes_avail;
+		if (zip->decrypted_bytes_remaining == 0)
+			zip->decrypted_ptr = zip->decrypted_buffer;
+		else
+			zip->decrypted_ptr += bytes_avail;
+	}
+	/* Calculate compressed data as much as we used.*/
+	if (zip->hctx_valid)
+		archive_hmac_sha1_update(&zip->hctx, sp, bytes_avail);
 	__archive_read_consume(a, bytes_avail);
 	zip->entry_bytes_remaining -= bytes_avail;
 	zip->entry_compressed_bytes_read += bytes_avail;
@@ -982,6 +1350,12 @@ zip_read_data_deflate(struct archive_read *a, const void **buff,
 	zip->entry_uncompressed_bytes_read += zip->stream.total_out;
 	*buff = zip->uncompressed_buffer;
 
+	if (zip->end_of_entry && zip->hctx_valid) {
+		r = check_authentication_code(a, NULL);
+		if (r != ARCHIVE_OK)
+			return (r);
+	}
+
 	if (zip->end_of_entry && (zip->entry->zip_flags & ZIP_LENGTH_AT_END)) {
 		const char *p;
 
@@ -1015,13 +1389,392 @@ zip_read_data_deflate(struct archive_read *a, const void **buff,
 #endif
 
 static int
+read_decryption_header(struct archive_read *a)
+{
+	struct zip *zip = (struct zip *)(a->format->data);
+	const char *p;
+	unsigned int remaining_size;
+	unsigned int ts;
+
+	/*
+	 * Read an initialization vector data field.
+	 */
+	p = __archive_read_ahead(a, 2, NULL);
+	if (p == NULL)
+		goto truncated;
+	ts = zip->iv_size;
+	zip->iv_size = archive_le16dec(p);
+	__archive_read_consume(a, 2);
+	if (ts < zip->iv_size) {
+		free(zip->iv);
+		zip->iv = NULL;
+	}
+	p = __archive_read_ahead(a, zip->iv_size, NULL);
+	if (p == NULL)
+		goto truncated;
+	if (zip->iv == NULL) {
+		zip->iv = malloc(zip->iv_size);
+		if (zip->iv == NULL)
+			goto nomem;
+	}
+	memcpy(zip->iv, p, zip->iv_size);
+	__archive_read_consume(a, zip->iv_size);
+
+	/*
+	 * Read a size of remaining decryption header field.
+	 */
+	p = __archive_read_ahead(a, 14, NULL);
+	if (p == NULL)
+		goto truncated;
+	remaining_size = archive_le32dec(p);
+	if (remaining_size < 16 || remaining_size > (1 << 18))
+		goto corrupted;
+
+	/* Check if format version is supported. */
+	if (archive_le16dec(p+4) != 3) {
+		archive_set_error(&a->archive,
+		    ARCHIVE_ERRNO_FILE_FORMAT,
+		    "Unsupported encryption format version: %u",
+		    archive_le16dec(p+4));
+		return (ARCHIVE_FAILED);
+	}
+
+	/*
+	 * Read an encryption algorithm field.
+	 */
+	zip->alg_id = archive_le16dec(p+6);
+	switch (zip->alg_id) {
+	case 0x6601:/* DES */
+	case 0x6602:/* RC2 */
+	case 0x6603:/* 3DES 168 */
+	case 0x6609:/* 3DES 112 */
+	case 0x660E:/* AES 128 */
+	case 0x660F:/* AES 192 */
+	case 0x6610:/* AES 256 */
+	case 0x6702:/* RC2 (version >= 5.2) */
+	case 0x6720:/* Blowfish */
+	case 0x6721:/* Twofish */
+	case 0x6801:/* RC4 */
+		/* Suuported encryption algorithm. */
+		break;
+	default:
+		archive_set_error(&a->archive,
+		    ARCHIVE_ERRNO_FILE_FORMAT,
+		    "Unknown encryption algorithm: %u", zip->alg_id);
+		return (ARCHIVE_FAILED);
+	}
+
+	/*
+	 * Read a bit length field.
+	 */
+	zip->bit_len = archive_le16dec(p+8);
+
+	/*
+	 * Read a flags field.
+	 */
+	zip->flags = archive_le16dec(p+10);
+	switch (zip->flags & 0xf000) {
+	case 0x0001: /* Password is required to decrypt. */
+	case 0x0002: /* Certificates only. */
+	case 0x0003: /* Password or certificate required to decrypt. */
+		break;
+	default:
+		archive_set_error(&a->archive,
+		    ARCHIVE_ERRNO_FILE_FORMAT,
+		    "Unknown encryption flag: %u", zip->flags);
+		return (ARCHIVE_FAILED);
+	}
+	if ((zip->flags & 0xf000) == 0 ||
+	    (zip->flags & 0xf000) == 0x4000) {
+		archive_set_error(&a->archive,
+		    ARCHIVE_ERRNO_FILE_FORMAT,
+		    "Unknown encryption flag: %u", zip->flags);
+		return (ARCHIVE_FAILED);
+	}
+
+	/*
+	 * Read an encrypted random data field.
+	 */
+	ts = zip->erd_size;
+	zip->erd_size = archive_le16dec(p+12);
+	__archive_read_consume(a, 14);
+	if ((zip->erd_size & 0xf) != 0 ||
+	    (zip->erd_size + 16) > remaining_size ||
+	    (zip->erd_size + 16) < zip->erd_size)
+		goto corrupted;
+
+	if (ts < zip->erd_size) {
+		free(zip->erd);
+		zip->erd = NULL;
+	}
+	p = __archive_read_ahead(a, zip->erd_size, NULL);
+	if (p == NULL)
+		goto truncated;
+	if (zip->erd == NULL) {
+		zip->erd = malloc(zip->erd_size);
+		if (zip->erd == NULL)
+			goto nomem;
+	}
+	memcpy(zip->erd, p, zip->erd_size);
+	__archive_read_consume(a, zip->erd_size);
+
+	/*
+	 * Read a reserved data field.
+	 */
+	p = __archive_read_ahead(a, 4, NULL);
+	if (p == NULL)
+		goto truncated;
+	/* Reserved data size should be zero. */
+	if (archive_le32dec(p) != 0)
+		goto corrupted;
+	__archive_read_consume(a, 4);
+
+	/*
+	 * Read a password validation data field.
+	 */
+	p = __archive_read_ahead(a, 2, NULL);
+	if (p == NULL)
+		goto truncated;
+	ts = zip->v_size;
+	zip->v_size = archive_le16dec(p);
+	__archive_read_consume(a, 2);
+	if ((zip->v_size & 0x0f) != 0 ||
+	    (zip->erd_size + zip->v_size + 16) > remaining_size ||
+	    (zip->erd_size + zip->v_size + 16) < (zip->erd_size + zip->v_size))
+		goto corrupted;
+	if (ts < zip->v_size) {
+		free(zip->v_data);
+		zip->v_data = NULL;
+	}
+	p = __archive_read_ahead(a, zip->v_size, NULL);
+	if (p == NULL)
+		goto truncated;
+	if (zip->v_data == NULL) {
+		zip->v_data = malloc(zip->v_size);
+		if (zip->v_data == NULL)
+			goto nomem;
+	}
+	memcpy(zip->v_data, p, zip->v_size);
+	__archive_read_consume(a, zip->v_size);
+
+	p = __archive_read_ahead(a, 4, NULL);
+	if (p == NULL)
+		goto truncated;
+	zip->v_crc32 = archive_le32dec(p);
+	__archive_read_consume(a, 4);
+
+	/*return (ARCHIVE_OK);
+	 * This is not fully implemnted yet.*/
+	archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+	    "Encrypted file is unsupported");
+	return (ARCHIVE_FAILED);
+truncated:
+	archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+	    "Truncated ZIP file data");
+	return (ARCHIVE_FATAL);
+corrupted:
+	archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+	    "Corrupted ZIP file data");
+	return (ARCHIVE_FATAL);
+nomem:
+	archive_set_error(&a->archive, ENOMEM,
+	    "No memory for ZIP decryption");
+	return (ARCHIVE_FATAL);
+}
+
+static int
+zip_alloc_decryption_buffer(struct archive_read *a)
+{
+	struct zip *zip = (struct zip *)(a->format->data);
+	size_t bs = 256 * 1024;
+
+	if (zip->decrypted_buffer == NULL) {
+		zip->decrypted_buffer_size = bs;
+		zip->decrypted_buffer = malloc(bs);
+		if (zip->decrypted_buffer == NULL) {
+			archive_set_error(&a->archive, ENOMEM,
+			    "No memory for ZIP decryption");
+			return (ARCHIVE_FATAL);
+		}
+	}
+	zip->decrypted_ptr = zip->decrypted_buffer;
+	return (ARCHIVE_OK);
+}
+
+static int
+init_traditional_PKWARE_decryption(struct archive_read *a)
+{
+	struct zip *zip = (struct zip *)(a->format->data);
+	const void *p;
+	int retry;
+	int r;
+
+	if (zip->tctx_valid)
+		return (ARCHIVE_OK);
+
+	/*
+	   Read the 12 bytes encryption header stored at
+	   the start of the data area.
+	 */
+#define ENC_HEADER_SIZE	12
+	if (0 == (zip->entry->zip_flags & ZIP_LENGTH_AT_END)
+	    && zip->entry_bytes_remaining < ENC_HEADER_SIZE) {
+		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+		    "Truncated Zip encrypted body: only %jd bytes available",
+		    (intmax_t)zip->entry_bytes_remaining);
+		return (ARCHIVE_FATAL);
+	}
+
+	p = __archive_read_ahead(a, ENC_HEADER_SIZE, NULL);
+	if (p == NULL) {
+		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+		    "Truncated ZIP file data");
+		return (ARCHIVE_FATAL);
+	}
+
+	for (retry = 0;; retry++) {
+		const char *passphrase;
+		uint8_t crcchk;
+
+		passphrase = __archive_read_next_passphrase(a);
+		if (passphrase == NULL) {
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+			    (retry > 0)?
+				"Incorrect passphrase":
+				"Passphrase required for this entry");
+			return (ARCHIVE_FAILED);
+		}
+
+		/*
+		 * Initialize ctx for Traditional PKWARE Decyption.
+		 */
+		r = trad_enc_init(&zip->tctx, passphrase, strlen(passphrase),
+			p, ENC_HEADER_SIZE, &crcchk);
+		if (r == 0 && crcchk == zip->entry->decdat)
+			break;/* The passphrase is OK. */
+		if (retry > 10000) {
+			/* Avoid infinity loop. */
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+			    "Too many incorrect passphrases");
+			return (ARCHIVE_FAILED);
+		}
+	}
+
+	__archive_read_consume(a, ENC_HEADER_SIZE);
+	zip->tctx_valid = 1;
+	if (0 == (zip->entry->zip_flags & ZIP_LENGTH_AT_END)) {
+	    zip->entry_bytes_remaining -= ENC_HEADER_SIZE;
+	}
+	/*zip->entry_uncompressed_bytes_read += ENC_HEADER_SIZE;*/
+	zip->entry_compressed_bytes_read += ENC_HEADER_SIZE;
+	zip->decrypted_bytes_remaining = 0;
+
+	return (zip_alloc_decryption_buffer(a));
+#undef ENC_HEADER_SIZE
+}
+
+static int
+init_WinZip_AES_decryption(struct archive_read *a)
+{
+	struct zip *zip = (struct zip *)(a->format->data);
+	const void *p;
+	const uint8_t *pv;
+	size_t key_len, salt_len;
+	uint8_t derived_key[MAX_DERIVED_KEY_BUF_SIZE];
+	int retry;
+	int r;
+
+	if (zip->cctx_valid || zip->hctx_valid)
+		return (ARCHIVE_OK);
+
+	switch (zip->entry->aes_extra.strength) {
+	case 1: salt_len = 8;  key_len = 16; break;
+	case 2: salt_len = 12; key_len = 24; break;
+	case 3: salt_len = 16; key_len = 32; break;
+	default: goto corrupted;
+	}
+	p = __archive_read_ahead(a, salt_len + 2, NULL);
+	if (p == NULL)
+		goto truncated;
+
+	for (retry = 0;; retry++) {
+		const char *passphrase;
+
+		passphrase = __archive_read_next_passphrase(a);
+		if (passphrase == NULL) {
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+			    (retry > 0)?
+				"Incorrect passphrase":
+				"Passphrase required for this entry");
+			return (ARCHIVE_FAILED);
+		}
+		memset(derived_key, 0, sizeof(derived_key));
+		r = archive_pbkdf2_sha1(passphrase, strlen(passphrase),
+		    p, salt_len, 1000, derived_key, key_len * 2 + 2);
+		if (r != 0) {
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+			    "Decryption is unsupported due to lack of "
+			    "crypto library");
+			return (ARCHIVE_FAILED);
+		}
+
+		/* Check password verification value. */
+		pv = ((const uint8_t *)p) + salt_len;
+		if (derived_key[key_len * 2] == pv[0] &&
+		    derived_key[key_len * 2 + 1] == pv[1])
+			break;/* The passphrase is OK. */
+		if (retry > 10000) {
+			/* Avoid infinity loop. */
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+			    "Too many incorrect passphrases");
+			return (ARCHIVE_FAILED);
+		}
+	}
+
+	r = archive_decrypto_aes_ctr_init(&zip->cctx, derived_key, key_len);
+	if (r != 0) {
+		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+		    "Decryption is unsupported due to lack of crypto library");
+		return (ARCHIVE_FAILED);
+	}
+	r = archive_hmac_sha1_init(&zip->hctx, derived_key + key_len, key_len);
+	if (r != 0) {
+		archive_decrypto_aes_ctr_release(&zip->cctx);
+		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+		    "Failed to initialize HMAC-SHA1");
+		return (ARCHIVE_FAILED);
+	}
+	zip->cctx_valid = zip->hctx_valid = 1;
+	__archive_read_consume(a, salt_len + 2);
+	zip->entry_bytes_remaining -= salt_len + 2 + AUTH_CODE_SIZE;
+	if (0 == (zip->entry->zip_flags & ZIP_LENGTH_AT_END)
+	    && zip->entry_bytes_remaining < 0)
+		goto corrupted;
+	zip->entry_compressed_bytes_read += salt_len + 2 + AUTH_CODE_SIZE;
+	zip->decrypted_bytes_remaining = 0;
+
+	zip->entry->compression = zip->entry->aes_extra.compression;
+	return (zip_alloc_decryption_buffer(a));
+
+truncated:
+	archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+	    "Truncated ZIP file data");
+	return (ARCHIVE_FATAL);
+corrupted:
+	archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+	    "Corrupted ZIP file data");
+	return (ARCHIVE_FATAL);
+}
+
+static int
 archive_read_format_zip_read_data(struct archive_read *a,
     const void **buff, size_t *size, int64_t *offset)
 {
 	int r;
 	struct zip *zip = (struct zip *)(a->format->data);
 
-	if (zip->has_encrypted_entries == ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW) {
+	if (zip->has_encrypted_entries ==
+			ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW) {
 		zip->has_encrypted_entries = 0;
 	}
 
@@ -1037,16 +1790,22 @@ archive_read_format_zip_read_data(struct archive_read *a,
 	if (AE_IFREG != (zip->entry->mode & AE_IFMT))
 		return (ARCHIVE_EOF);
 
-	if (zip->entry->zip_flags & (ZIP_ENCRYPTED | ZIP_STRONG_ENCRYPTED)) {
-		zip->has_encrypted_entries = 1;
-		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
-		    "Encrypted file is unsupported");
-		return (ARCHIVE_FAILED);
-	}
-
 	__archive_read_consume(a, zip->unconsumed);
 	zip->unconsumed = 0;
 
+	if (zip->init_decryption) {
+		zip->has_encrypted_entries = 1;
+		if (zip->entry->zip_flags & ZIP_STRONG_ENCRYPTED)
+			r = read_decryption_header(a);
+		else if (zip->entry->compression == WINZIP_AES_ENCRYPTION)
+			r = init_WinZip_AES_decryption(a);
+		else
+			r = init_traditional_PKWARE_decryption(a);
+		if (r != ARCHIVE_OK)
+			return (r);
+		zip->init_decryption = 0;
+	}
+
 	switch(zip->entry->compression) {
 	case 0:  /* No compression. */
 		r =  zip_read_data_none(a, buff, size, offset);
@@ -1096,7 +1855,9 @@ archive_read_format_zip_read_data(struct archive_read *a,
 			return (ARCHIVE_WARN);
 		}
 		/* Check computed CRC against header */
-		if (zip->entry->crc32 != zip->entry_crc32
+		if ((!zip->hctx_valid ||
+		      zip->entry->aes_extra.vendor != AES_VENDOR_AE_2) &&
+		   zip->entry->crc32 != zip->entry_crc32
 		    && !zip->ignore_crc32) {
 			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
 			    "ZIP bad CRC: 0x%lx should be 0x%lx",
@@ -1130,6 +1891,15 @@ archive_read_format_zip_cleanup(struct archive_read *a)
 			zip_entry = next_zip_entry;
 		}
 	}
+	free(zip->decrypted_buffer);
+	if (zip->cctx_valid)
+		archive_decrypto_aes_ctr_release(&zip->cctx);
+	if (zip->hctx_valid)
+		archive_hmac_sha1_cleanup(&zip->hctx);
+	free(zip->iv);
+	free(zip->erd);
+	free(zip->v_data);
+	archive_string_free(&zip->format_name);
 	free(zip);
 	(a->format->data) = NULL;
 	return (ARCHIVE_OK);
@@ -1217,7 +1987,8 @@ static int
 archive_read_support_format_zip_capabilities_streamable(struct archive_read * a)
 {
 	(void)a; /* UNUSED */
-	return (ARCHIVE_READ_FORMAT_CAPS_ENCRYPT_DATA | ARCHIVE_READ_FORMAT_CAPS_ENCRYPT_METADATA);
+	return (ARCHIVE_READ_FORMAT_CAPS_ENCRYPT_DATA |
+		ARCHIVE_READ_FORMAT_CAPS_ENCRYPT_METADATA);
 }
 
 static int
@@ -1275,9 +2046,9 @@ archive_read_format_zip_streamable_read_header(struct archive_read *a,
 	 * archive_read_data(), so be it. We'll do the same check there
 	 * as well.
 	 */
-	if (zip->has_encrypted_entries == ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW) {
+	if (zip->has_encrypted_entries ==
+			ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW)
 		zip->has_encrypted_entries = 0;
-	}
 
 	/* Make sure we have a zip_entry structure to use. */
 	if (zip->zip_entries == NULL) {
@@ -1291,6 +2062,13 @@ archive_read_format_zip_streamable_read_header(struct archive_read *a,
 	zip->entry = zip->zip_entries;
 	memset(zip->entry, 0, sizeof(struct zip_entry));
 
+	if (zip->cctx_valid)
+		archive_decrypto_aes_ctr_release(&zip->cctx);
+	if (zip->hctx_valid)
+		archive_hmac_sha1_cleanup(&zip->hctx);
+	zip->tctx_valid = zip->cctx_valid = zip->hctx_valid = 0;
+	__archive_read_reset_passphrase(a);
+
 	/* Search ahead for the next local file header. */
 	__archive_read_consume(a, zip->unconsumed);
 	zip->unconsumed = 0;
@@ -1363,12 +2141,28 @@ archive_read_format_zip_read_data_skip_streamable(struct archive_read *a)
 	if (0 == (zip->entry->zip_flags & ZIP_LENGTH_AT_END)
 	    || zip->entry->compressed_size > 0) {
 		/* We know the compressed length, so we can just skip. */
-		bytes_skipped = __archive_read_consume(a, zip->entry_bytes_remaining);
+		bytes_skipped = __archive_read_consume(a,
+					zip->entry_bytes_remaining);
 		if (bytes_skipped < 0)
 			return (ARCHIVE_FATAL);
 		return (ARCHIVE_OK);
 	}
 
+	if (zip->init_decryption) {
+		int r;
+
+		zip->has_encrypted_entries = 1;
+		if (zip->entry->zip_flags & ZIP_STRONG_ENCRYPTED)
+			r = read_decryption_header(a);
+		else if (zip->entry->compression == WINZIP_AES_ENCRYPTION)
+			r = init_WinZip_AES_decryption(a);
+		else
+			r = init_traditional_PKWARE_decryption(a);
+		if (r != ARCHIVE_OK)
+			return (r);
+		zip->init_decryption = 0;
+	}
+
 	/* We're streaming and we don't know the length. */
 	/* If the body is compressed and we know the format, we can
 	 * find an exact end-of-entry by decompressing it. */
@@ -1406,9 +2200,11 @@ archive_read_format_zip_read_data_skip_streamable(struct archive_read *a)
 				else if (p[3] == '\010' && p[2] == '\007'
 				    && p[1] == 'K' && p[0] == 'P') {
 					if (zip->entry->flags & LA_USED_ZIP64)
-						__archive_read_consume(a, p - buff + 24);
+						__archive_read_consume(a,
+						    p - buff + 24);
 					else
-						__archive_read_consume(a, p - buff + 16);
+						__archive_read_consume(a,
+						    p - buff + 16);
 					return ARCHIVE_OK;
 				} else { p += 4; }
 			}
@@ -1427,13 +2223,12 @@ archive_read_support_format_zip_streamable(struct archive *_a)
 	archive_check_magic(_a, ARCHIVE_READ_MAGIC,
 	    ARCHIVE_STATE_NEW, "archive_read_support_format_zip");
 
-	zip = (struct zip *)malloc(sizeof(*zip));
+	zip = (struct zip *)calloc(1, sizeof(*zip));
 	if (zip == NULL) {
 		archive_set_error(&a->archive, ENOMEM,
 		    "Can't allocate zip data");
 		return (ARCHIVE_FATAL);
 	}
-	memset(zip, 0, sizeof(*zip));
 
 	/* Streamable reader doesn't support mac extensions. */
 	zip->process_mac_extensions = 0;
@@ -1473,7 +2268,8 @@ static int
 archive_read_support_format_zip_capabilities_seekable(struct archive_read * a)
 {
 	(void)a; /* UNUSED */
-	return (ARCHIVE_READ_FORMAT_CAPS_ENCRYPT_DATA | ARCHIVE_READ_FORMAT_CAPS_ENCRYPT_METADATA);
+	return (ARCHIVE_READ_FORMAT_CAPS_ENCRYPT_DATA |
+		ARCHIVE_READ_FORMAT_CAPS_ENCRYPT_METADATA);
 }
 
 /*
@@ -1514,7 +2310,11 @@ read_eocd(struct zip *zip, const char *p, int64_t current_offset)
 	return 32;
 }
 
-static int
+/*
+ * Examine Zip64 EOCD locator:  If it's valid, store the information
+ * from it.
+ */
+static void
 read_zip64_eocd(struct archive_read *a, struct zip *zip, const char *p)
 {
 	int64_t eocd64_offset;
@@ -1524,37 +2324,35 @@ read_zip64_eocd(struct archive_read *a, struct zip *zip, const char *p)
 
 	/* Central dir must be on first volume. */
 	if (archive_le32dec(p + 4) != 0)
-		return 0;
+		return;
 	/* Must be only a single volume. */
 	if (archive_le32dec(p + 16) != 1)
-		return 0;
+		return;
 
 	/* Find the Zip64 EOCD record. */
 	eocd64_offset = archive_le64dec(p + 8);
 	if (__archive_read_seek(a, eocd64_offset, SEEK_SET) < 0)
-		return 0;
+		return;
 	if ((p = __archive_read_ahead(a, 56, NULL)) == NULL)
-		return 0;
+		return;
 	/* Make sure we can read all of it. */
 	eocd64_size = archive_le64dec(p + 4) + 12;
 	if (eocd64_size < 56 || eocd64_size > 16384)
-		return 0;
-	if ((p = __archive_read_ahead(a, eocd64_size, NULL)) == NULL)
-		return 0;
+		return;
+	if ((p = __archive_read_ahead(a, (size_t)eocd64_size, NULL)) == NULL)
+		return;
 
 	/* Sanity-check the EOCD64 */
 	if (archive_le32dec(p + 16) != 0) /* Must be disk #0 */
-		return 0;
+		return;
 	if (archive_le32dec(p + 20) != 0) /* CD must be on disk #0 */
-		return 0;
+		return;
 	/* CD can't be split. */
 	if (archive_le64dec(p + 24) != archive_le64dec(p + 32))
-		return 0;
+		return;
 
 	/* Save the central directory offset for later use. */
 	zip->central_directory_offset = archive_le64dec(p + 48);
-
-	return 32;
 }
 
 static int
@@ -1575,40 +2373,39 @@ archive_read_format_zip_seekable_bid(struct archive_read *a, int best_bid)
 		return 0;
 
 	/* Search last 16k of file for end-of-central-directory
-	 * record (which starts with PK\005\006) or Zip64 locator
-	 * record (which begins with PK\006\007) */
-	tail = zipmin(1024 * 16, file_size);
+	 * record (which starts with PK\005\006) */
+	tail = (int)zipmin(1024 * 16, file_size);
 	current_offset = __archive_read_seek(a, -tail, SEEK_END);
 	if (current_offset < 0)
 		return 0;
 	if ((p = __archive_read_ahead(a, (size_t)tail, NULL)) == NULL)
 		return 0;
-	/* TODO: Rework this to search backwards from the end.  We
-	 * normally expect the EOCD record to be at the very end, so
-	 * that should be significantly faster.  Tricky part: Make
-	 * sure we still prefer the Zip64 locator if it's present. */
-	for (i = 0; i <= tail - 22;) {
-		switch (p[i + 3]) {
-		case 'P': i += 3; break;
-		case 'K': i += 2; break;
-		case 005: i += 1; break;
-		case 006:
+	/* Boyer-Moore search backwards from the end, since we want
+	 * to match the last EOCD in the file (there can be more than
+	 * one if there is an uncompressed Zip archive as a member
+	 * within this Zip archive). */
+	for (i = tail - 22; i > 0;) {
+		switch (p[i]) {
+		case 'P':
 			if (memcmp(p + i, "PK\005\006", 4) == 0) {
-				int ret = read_eocd(zip, p + i, current_offset + i);
-				if (ret > 0)
-					return (ret);
-			}
-			i += 1; /* Look for PK\006\007 next */
-			break;
-		case 007:
-			if (memcmp(p + i, "PK\006\007", 4) == 0) {
-				int ret = read_zip64_eocd(a, zip, p + i);
-				if (ret > 0)
+				int ret = read_eocd(zip, p + i,
+				    current_offset + i);
+				if (ret > 0) {
+					/* Zip64 EOCD locator precedes
+					 * regular EOCD if present. */
+					if (i >= 20
+					    && memcmp(p + i - 20, "PK\006\007", 4) == 0) {
+						read_zip64_eocd(a, zip, p + i - 20);
+					}
 					return (ret);
+				}
 			}
-			i += 4;
+			i -= 4;
 			break;
-		default: i += 4; break;
+		case 'K': i -= 1; break;
+		case 005: i -= 2; break;
+		case 006: i -= 3; break;
+		default: i -= 4; break;
 		}
 	}
 	return 0;
@@ -1760,7 +2557,8 @@ slurp_central_directory(struct archive_read *a, struct zip *zip)
 		}
 		__archive_read_consume(a, i);
 	}
-	correction = archive_filter_bytes(&a->archive, 0) - zip->central_directory_offset;
+	correction = archive_filter_bytes(&a->archive, 0)
+			- zip->central_directory_offset;
 
 	__archive_rb_tree_init(&zip->tree, &rb_ops);
 	__archive_rb_tree_init(&zip->tree_rsrc, &rb_rsrc_ops);
@@ -1795,12 +2593,17 @@ slurp_central_directory(struct archive_read *a, struct zip *zip)
 		zip_entry->system = p[5];
 		/* version_required = archive_le16dec(p + 6); */
 		zip_entry->zip_flags = archive_le16dec(p + 8);
-		if (zip_entry->zip_flags & (ZIP_ENCRYPTED | ZIP_STRONG_ENCRYPTED)){
+		if (zip_entry->zip_flags
+		      & (ZIP_ENCRYPTED | ZIP_STRONG_ENCRYPTED)){
 			zip->has_encrypted_entries = 1;
 		}
 		zip_entry->compression = (char)archive_le16dec(p + 10);
 		zip_entry->mtime = zip_time(p + 12);
 		zip_entry->crc32 = archive_le32dec(p + 16);
+		if (zip_entry->zip_flags & ZIP_LENGTH_AT_END)
+			zip_entry->decdat = p[13];
+		else
+			zip_entry->decdat = p[19];
 		zip_entry->compressed_size = archive_le32dec(p + 20);
 		zip_entry->uncompressed_size = archive_le32dec(p + 24);
 		filename_length = archive_le16dec(p + 28);
@@ -1823,9 +2626,11 @@ slurp_central_directory(struct archive_read *a, struct zip *zip)
 		/* We're done with the regular data; get the filename and
 		 * extra data. */
 		__archive_read_consume(a, 46);
-		if ((p = __archive_read_ahead(a, filename_length + extra_length, NULL))
-		    == NULL) {
-			archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+		p = __archive_read_ahead(a, filename_length + extra_length,
+			NULL);
+		if (p == NULL) {
+			archive_set_error(&a->archive,
+			    ARCHIVE_ERRNO_FILE_FORMAT,
 			    "Truncated ZIP file header");
 			return ARCHIVE_FATAL;
 		}
@@ -1850,26 +2655,30 @@ slurp_central_directory(struct archive_read *a, struct zip *zip)
 				 * resource fork file to expose it. */
 				if (name[filename_length-1] != '/' &&
 				    (r - name < 3 || r[0] != '.' || r[1] != '_')) {
-					__archive_rb_tree_insert_node(&zip->tree,
-					    &zip_entry->node);
+					__archive_rb_tree_insert_node(
+					    &zip->tree, &zip_entry->node);
 					/* Expose its parent directories. */
-					expose_parent_dirs(zip, name, filename_length);
+					expose_parent_dirs(zip, name,
+					    filename_length);
 				} else {
 					/* This file is a resource fork file or
 					 * a directory. */
-					archive_strncpy(&(zip_entry->rsrcname), name,
-					    filename_length);
-					__archive_rb_tree_insert_node(&zip->tree_rsrc,
-					    &zip_entry->node);
+					archive_strncpy(&(zip_entry->rsrcname),
+					     name, filename_length);
+					__archive_rb_tree_insert_node(
+					    &zip->tree_rsrc, &zip_entry->node);
 				}
 			} else {
-				/* Generate resource fork name to find its resource
-				 * file at zip->tree_rsrc. */
-				archive_strcpy(&(zip_entry->rsrcname), "__MACOSX/");
-				archive_strncat(&(zip_entry->rsrcname), name, r - name);
+				/* Generate resource fork name to find its
+				 * resource file at zip->tree_rsrc. */
+				archive_strcpy(&(zip_entry->rsrcname),
+				    "__MACOSX/");
+				archive_strncat(&(zip_entry->rsrcname),
+				    name, r - name);
 				archive_strcat(&(zip_entry->rsrcname), "._");
 				archive_strncat(&(zip_entry->rsrcname),
-				    name + (r - name), filename_length - (r - name));
+				    name + (r - name),
+				    filename_length - (r - name));
 				/* Register an entry to RB tree to sort it by
 				 * file offset. */
 				__archive_rb_tree_insert_node(&zip->tree,
@@ -2060,9 +2869,9 @@ archive_read_format_zip_seekable_read_header(struct archive_read *a,
 	 * archive_read_data(), so be it. We'll do the same check there
 	 * as well.
 	 */
-	if (zip->has_encrypted_entries == ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW) {
+	if (zip->has_encrypted_entries ==
+			ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW)
 		zip->has_encrypted_entries = 0;
-	}
 
 	a->archive.archive_format = ARCHIVE_FORMAT_ZIP;
 	if (a->archive.archive_format_name == NULL)
@@ -2091,6 +2900,13 @@ archive_read_format_zip_seekable_read_header(struct archive_read *a,
 	else
 		rsrc = NULL;
 
+	if (zip->cctx_valid)
+		archive_decrypto_aes_ctr_release(&zip->cctx);
+	if (zip->hctx_valid)
+		archive_hmac_sha1_cleanup(&zip->hctx);
+	zip->tctx_valid = zip->cctx_valid = zip->hctx_valid = 0;
+	__archive_read_reset_passphrase(a);
+
 	/* File entries are sorted by the header offset, we should mostly
 	 * use __archive_read_consume to advance a read point to avoid redundant
 	 * data reading.  */
@@ -2099,7 +2915,8 @@ archive_read_format_zip_seekable_read_header(struct archive_read *a,
 		__archive_read_consume(a,
 		    zip->entry->local_header_offset - offset);
 	else if (offset != zip->entry->local_header_offset) {
-		__archive_read_seek(a, zip->entry->local_header_offset, SEEK_SET);
+		__archive_read_seek(a, zip->entry->local_header_offset,
+		    SEEK_SET);
 	}
 	zip->unconsumed = 0;
 	r = zip_read_local_file_header(a, entry, zip);
@@ -2137,13 +2954,12 @@ archive_read_support_format_zip_seekable(struct archive *_a)
 	archive_check_magic(_a, ARCHIVE_READ_MAGIC,
 	    ARCHIVE_STATE_NEW, "archive_read_support_format_zip_seekable");
 
-	zip = (struct zip *)malloc(sizeof(*zip));
+	zip = (struct zip *)calloc(1, sizeof(*zip));
 	if (zip == NULL) {
 		archive_set_error(&a->archive, ENOMEM,
 		    "Can't allocate zip data");
 		return (ARCHIVE_FATAL);
 	}
-	memset(zip, 0, sizeof(*zip));
 
 #ifdef HAVE_COPYFILE_H
 	/* Set this by default on Mac OS. */