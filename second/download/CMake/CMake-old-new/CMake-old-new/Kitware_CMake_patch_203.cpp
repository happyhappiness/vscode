@@ -1,7 +1,7 @@
 /*-
  * Copyright (c) 2008 Anselm Strauss
  * Copyright (c) 2009 Joerg Sonnenberger
- * Copyright (c) 2011-2012 Michihiro NAKAJIMA
+ * Copyright (c) 2011-2012,2014 Michihiro NAKAJIMA
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
@@ -49,20 +49,23 @@ __FBSDID("$FreeBSD: head/lib/libarchive/archive_write_set_format_zip.c 201168 20
 #endif
 
 #include "archive.h"
+#include "archive_cryptor_private.h"
 #include "archive_endian.h"
 #include "archive_entry.h"
 #include "archive_entry_locale.h"
+#include "archive_hmac_private.h"
 #include "archive_private.h"
+#include "archive_random_private.h"
 #include "archive_write_private.h"
 
 #ifndef HAVE_ZLIB_H
 #include "archive_crc32.h"
 #endif
 
+#define ZIP_ENTRY_FLAG_ENCRYPTED	(1<<0)
 #define ZIP_ENTRY_FLAG_LENGTH_AT_END	(1<<3)
 #define ZIP_ENTRY_FLAG_UTF8_NAME	(1 << 11)
 
-
 enum compression {
 	COMPRESSION_UNSPECIFIED = -1,
 	COMPRESSION_STORE = 0,
@@ -75,16 +78,42 @@ enum compression {
 #define COMPRESSION_DEFAULT	COMPRESSION_STORE
 #endif
 
+enum encryption {
+	ENCRYPTION_NONE	= 0,
+	ENCRYPTION_TRADITIONAL, /* Traditional PKWARE encryption. */
+	ENCRYPTION_WINZIP_AES128, /* WinZIP AES-128 encryption. */
+	ENCRYPTION_WINZIP_AES256, /* WinZIP AES-256 encryption. */
+};
+
+#define TRAD_HEADER_SIZE	12
+/*
+ * See "WinZip - AES Encryption Information"
+ *     http://www.winzip.com/aes_info.htm
+ */
+/* Value used in compression method. */
+#define WINZIP_AES_ENCRYPTION	99
+/* A WinZip AES header size which is stored at the beginning of
+ * file contents. */
+#define WINZIP_AES128_HEADER_SIZE	(8 + 2)
+#define WINZIP_AES256_HEADER_SIZE	(16 + 2)
+/* AES vendor version. */
+#define AES_VENDOR_AE_1 0x0001
+#define AES_VENDOR_AE_2 0x0002
+/* Authentication code size. */
+#define AUTH_CODE_SIZE		10
+/**/
+#define MAX_DERIVED_KEY_BUF_SIZE (AES_MAX_KEY_SIZE * 2 + 2)
+
 struct cd_segment {
 	struct cd_segment *next;
 	size_t buff_size;
 	unsigned char *buff;
 	unsigned char *p;
 };
 
-/* Bits used to enable/disable certain experimental features. */
-#define	EXPERIMENT_LA 1
-#define	EXPERIMENTS_ALL 0xffff
+struct trad_enc_ctx {
+	uint32_t keys[3];
+};
 
 struct zip {
 
@@ -97,9 +126,18 @@ struct zip {
 	struct archive_entry *entry;
 	uint32_t entry_crc32;
 	enum compression entry_compression;
+	enum encryption  entry_encryption;
 	int entry_flags;
 	int entry_uses_zip64;
 	int experiments;
+	struct trad_enc_ctx tctx;
+	char tctx_valid;
+	unsigned char trad_chkdat;
+	unsigned aes_vendor;
+	archive_crypto_ctx cctx;
+	char cctx_valid;
+	archive_hmac_sha1_ctx hctx;
+	char hctx_valid;
 
 	unsigned char *file_header;
 	size_t file_header_extra_offset;
@@ -115,18 +153,20 @@ struct zip {
 	struct archive_string_conv *opt_sconv;
 	struct archive_string_conv *sconv_default;
 	enum compression requested_compression;
+	int deflate_compression_level;
 	int init_default_conversion;
+	enum encryption  encryption_type;
 
 #define ZIP_FLAG_AVOID_ZIP64 1
 #define ZIP_FLAG_FORCE_ZIP64 2
-#define ZIP_FLAG_EXPERIMENT_EL 4
+#define ZIP_FLAG_EXPERIMENT_xl 4
 	int flags;
 
 #ifdef HAVE_ZLIB_H
 	z_stream stream;
+#endif
 	size_t len_buf;
 	unsigned char *buf;
-#endif
 };
 
 /* Don't call this min or MIN, since those are already defined
@@ -147,6 +187,13 @@ static size_t path_length(struct archive_entry *);
 static int write_path(struct archive_entry *, struct archive_write *);
 static void copy_path(struct archive_entry *, unsigned char *);
 static struct archive_string_conv *get_sconv(struct archive_write *, struct zip *);
+static int trad_enc_init(struct trad_enc_ctx *, const char *, size_t);
+static unsigned trad_enc_encrypt_update(struct trad_enc_ctx *, const uint8_t *,
+    size_t, uint8_t *, size_t);
+static int init_traditional_pkware_encryption(struct archive_write *);
+static int is_traditional_pkware_encryption_supported(void);
+static int init_winzip_aes_encryption(struct archive_write *);
+static int is_winzip_aes_encryption_supported(int encryption);
 
 static unsigned char *
 cd_alloc(struct zip *zip, size_t length)
@@ -186,7 +233,7 @@ cd_alloc(struct zip *zip, size_t length)
 static unsigned long
 real_crc32(unsigned long crc, const void *buff, size_t len)
 {
-	return crc32(crc, buff, len);
+	return crc32(crc, buff, (unsigned int)len);
 }
 
 static unsigned long
@@ -227,11 +274,70 @@ archive_write_zip_options(struct archive_write *a, const char *key,
 			ret = ARCHIVE_OK;
 		}
 		return (ret);
+	} else if (strcmp(key, "compression-level") == 0) {
+		if (val == NULL || !(val[0] >= '0' && val[0] <= '9') || val[1] != '\0') {
+			return ARCHIVE_WARN;
+		}
+
+		if (val[0] == '0') {
+			zip->requested_compression = COMPRESSION_STORE;
+			return ARCHIVE_OK;
+		} else {
+#ifdef HAVE_ZLIB_H
+			zip->requested_compression = COMPRESSION_DEFLATE;
+			zip->deflate_compression_level = val[0] - '0';
+			return ARCHIVE_OK;
+#else
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+			    "deflate compression not supported");
+#endif
+		}
+	} else if (strcmp(key, "encryption") == 0) {
+		if (val == NULL) {
+			zip->encryption_type = ENCRYPTION_NONE;
+			ret = ARCHIVE_OK;
+		} else if (val[0] == '1' || strcmp(val, "traditional") == 0
+		    || strcmp(val, "zipcrypt") == 0
+		    || strcmp(val, "ZipCrypt") == 0) {
+			if (is_traditional_pkware_encryption_supported()) {
+				zip->encryption_type = ENCRYPTION_TRADITIONAL;
+				ret = ARCHIVE_OK;
+			} else {
+				archive_set_error(&a->archive,
+				    ARCHIVE_ERRNO_MISC,
+				    "encryption not supported");
+			}
+		} else if (strcmp(val, "aes128") == 0) {
+			if (is_winzip_aes_encryption_supported(
+			    ENCRYPTION_WINZIP_AES128)) {
+				zip->encryption_type = ENCRYPTION_WINZIP_AES128;
+				ret = ARCHIVE_OK;
+			} else {
+				archive_set_error(&a->archive,
+				    ARCHIVE_ERRNO_MISC,
+				    "encryption not supported");
+			}
+		} else if (strcmp(val, "aes256") == 0) {
+			if (is_winzip_aes_encryption_supported(
+			    ENCRYPTION_WINZIP_AES256)) {
+				zip->encryption_type = ENCRYPTION_WINZIP_AES256;
+				ret = ARCHIVE_OK;
+			} else {
+				archive_set_error(&a->archive,
+				    ARCHIVE_ERRNO_MISC,
+				    "encryption not supported");
+			}
+		} else {
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+			    "%s: unknown encryption '%s'",
+			    a->format_name, val);
+		}
+		return (ret);
 	} else if (strcmp(key, "experimental") == 0) {
 		if (val == NULL || val[0] == 0) {
-			zip->flags &= ~ ZIP_FLAG_EXPERIMENT_EL;
+			zip->flags &= ~ ZIP_FLAG_EXPERIMENT_xl;
 		} else {
-			zip->flags |= ZIP_FLAG_EXPERIMENT_EL;
+			zip->flags |= ZIP_FLAG_EXPERIMENT_xl;
 		}
 		return (ARCHIVE_OK);
 	} else if (strcmp(key, "fakecrc32") == 0) {
@@ -357,9 +463,12 @@ archive_write_set_format_zip(struct archive *_a)
 
 	/* "Unspecified" lets us choose the appropriate compression. */
 	zip->requested_compression = COMPRESSION_UNSPECIFIED;
+#ifdef HAVE_ZLIB_H
+	zip->deflate_compression_level = Z_DEFAULT_COMPRESSION;
+#endif
 	zip->crc32func = real_crc32;
 
-#ifdef HAVE_ZLIB_H
+	/* A buffer used for both compression and encryption. */
 	zip->len_buf = 65536;
 	zip->buf = malloc(zip->len_buf);
 	if (zip->buf == NULL) {
@@ -368,7 +477,6 @@ archive_write_set_format_zip(struct archive *_a)
 		    "Can't allocate compression buffer");
 		return (ARCHIVE_FATAL);
 	}
-#endif
 
 	a->format_data = zip;
 	a->format_name = "zip";
@@ -400,7 +508,7 @@ static int
 archive_write_zip_header(struct archive_write *a, struct archive_entry *entry)
 {
 	unsigned char local_header[32];
-	unsigned char local_extra[128];
+	unsigned char local_extra[144];
 	struct zip *zip = a->format_data;
 	unsigned char *e;
 	unsigned char *cd_extra;
@@ -409,7 +517,6 @@ archive_write_zip_header(struct archive_write *a, struct archive_entry *entry)
 	size_t slink_size = 0;
 	struct archive_string_conv *sconv = get_sconv(a, zip);
 	int ret, ret2 = ARCHIVE_OK;
-	int64_t size;
 	mode_t type;
 	int version_needed = 10;
 
@@ -453,11 +560,34 @@ archive_write_zip_header(struct archive_write *a, struct archive_entry *entry)
 	zip->entry_flags = 0;
 	zip->entry_uses_zip64 = 0;
 	zip->entry_crc32 = zip->crc32func(0, NULL, 0);
+	zip->entry_encryption = 0;
 	if (zip->entry != NULL) {
 		archive_entry_free(zip->entry);
 		zip->entry = NULL;
 	}
 
+	if (zip->cctx_valid)
+		archive_encrypto_aes_ctr_release(&zip->cctx);
+	if (zip->hctx_valid)
+		archive_hmac_sha1_cleanup(&zip->hctx);
+	zip->tctx_valid = zip->cctx_valid = zip->hctx_valid = 0;
+
+	if (type == AE_IFREG
+		    &&(!archive_entry_size_is_set(entry)
+			|| archive_entry_size(entry) > 0)) {
+		switch (zip->encryption_type) {
+		case ENCRYPTION_TRADITIONAL:
+		case ENCRYPTION_WINZIP_AES128:
+		case ENCRYPTION_WINZIP_AES256:
+			zip->entry_flags |= ZIP_ENTRY_FLAG_ENCRYPTED;
+			zip->entry_encryption = zip->encryption_type;
+			break;
+		default:
+			break;
+		}
+	}
+
+
 #if defined(_WIN32) && !defined(__CYGWIN__)
 	/* Make sure the path separators in pahtname, hardlink and symlink
 	 * are all slash '/', not the Windows path separator '\'. */
@@ -543,10 +673,11 @@ archive_write_zip_header(struct archive_write *a, struct archive_entry *entry)
 	} else if (type != AE_IFREG) {
 		zip->entry_compression = COMPRESSION_STORE;
 		zip->entry_uncompressed_limit = 0;
-		size = 0;
 		version_needed = 20;
 	} else if (archive_entry_size_is_set(zip->entry)) {
-		size = archive_entry_size(zip->entry);
+		int64_t size = archive_entry_size(zip->entry);
+		int64_t additional_size = 0;
+
 		zip->entry_uncompressed_limit = size;
 		zip->entry_compression = zip->requested_compression;
 		if (zip->entry_compression == COMPRESSION_UNSPECIFIED) {
@@ -560,18 +691,56 @@ archive_write_zip_header(struct archive_write *a, struct archive_entry *entry)
 			zip->entry_uncompressed_size = size;
 			version_needed = 20;
 		}
-		if ((zip->flags & ZIP_FLAG_FORCE_ZIP64) /* User asked. */
-		    || (zip->entry_uncompressed_size > 0xffffffffLL)) { /* Large entry. */
+
+		if (zip->entry_flags & ZIP_ENTRY_FLAG_ENCRYPTED) {
+			switch (zip->entry_encryption) {
+			case ENCRYPTION_TRADITIONAL:
+				additional_size = TRAD_HEADER_SIZE;
+				version_needed = 20;
+				break;
+			case ENCRYPTION_WINZIP_AES128:
+				additional_size = WINZIP_AES128_HEADER_SIZE
+				    + AUTH_CODE_SIZE;
+				version_needed = 20;
+				break;
+			case ENCRYPTION_WINZIP_AES256:
+				additional_size = WINZIP_AES256_HEADER_SIZE
+				    + AUTH_CODE_SIZE;
+				version_needed = 20;
+				break;
+			default:
+				break;
+			}
+			if (zip->entry_compression == COMPRESSION_STORE)
+				zip->entry_compressed_size += additional_size;
+		}
+
+		/*
+		 * Set Zip64 extension in any of the following cases
+		 * (this was suggested by discussion on info-zip-dev
+		 * mailing list):
+		 *  = Zip64 is being forced by user
+		 *  = File is over 4GiB uncompressed
+		 *    (including encryption header, if any)
+		 *  = File is close to 4GiB and is being compressed
+		 *    (compression might make file larger)
+		 */
+		if ((zip->flags & ZIP_FLAG_FORCE_ZIP64)
+		    || (zip->entry_uncompressed_size + additional_size > 0xffffffffLL)
+		    || (zip->entry_uncompressed_size > 0xff000000LL
+			&& zip->entry_compression != COMPRESSION_STORE)) {
 			zip->entry_uses_zip64 = 1;
 			version_needed = 45;
 		}
 
 		/* We may know the size, but never the CRC. */
 		zip->entry_flags |= ZIP_ENTRY_FLAG_LENGTH_AT_END;
 	} else {
-		/* Prefer deflate if it's available, because deflate
-		 * has a clear end-of-data marker that makes
-		 * length-at-end more reliable. */
+		/* We don't know the size.  In this case, we prefer
+		 * deflate (it has a clear end-of-data marker which
+		 * makes length-at-end more reliable) and will
+		 * enable Zip64 extensions unless we're told not to.
+		 */
 		zip->entry_compression = COMPRESSION_DEFAULT;
 		zip->entry_flags |= ZIP_ENTRY_FLAG_LENGTH_AT_END;
 		if ((zip->flags & ZIP_FLAG_AVOID_ZIP64) == 0) {
@@ -582,15 +751,33 @@ archive_write_zip_header(struct archive_write *a, struct archive_entry *entry)
 		} else {
 			version_needed = 20;
 		}
+
+		if (zip->entry_flags & ZIP_ENTRY_FLAG_ENCRYPTED) {
+			switch (zip->entry_encryption) {
+			case ENCRYPTION_TRADITIONAL:
+			case ENCRYPTION_WINZIP_AES128:
+			case ENCRYPTION_WINZIP_AES256:
+				if (version_needed < 20)
+					version_needed = 20;
+				break;
+			default:
+				break;
+			}
+		}
 	}
 
 	/* Format the local header. */
 	memset(local_header, 0, sizeof(local_header));
 	memcpy(local_header, "PK\003\004", 4);
 	archive_le16enc(local_header + 4, version_needed);
 	archive_le16enc(local_header + 6, zip->entry_flags);
-	archive_le16enc(local_header + 8, zip->entry_compression);
-	archive_le32enc(local_header + 10, dos_time(archive_entry_mtime(zip->entry)));
+	if (zip->entry_encryption == ENCRYPTION_WINZIP_AES128
+	    || zip->entry_encryption == ENCRYPTION_WINZIP_AES256)
+		archive_le16enc(local_header + 8, WINZIP_AES_ENCRYPTION);
+	else
+		archive_le16enc(local_header + 8, zip->entry_compression);
+	archive_le32enc(local_header + 10,
+		dos_time(archive_entry_mtime(zip->entry)));
 	archive_le32enc(local_header + 14, zip->entry_crc32);
 	if (zip->entry_uses_zip64) {
 		/* Zip64 data in the local header "must" include both
@@ -601,10 +788,17 @@ archive_write_zip_header(struct archive_write *a, struct archive_entry *entry)
 		archive_le32enc(local_header + 18, 0xffffffffLL);
 		archive_le32enc(local_header + 22, 0xffffffffLL);
 	} else {
-		archive_le32enc(local_header + 18, zip->entry_compressed_size);
-		archive_le32enc(local_header + 22, zip->entry_uncompressed_size);
+		archive_le32enc(local_header + 18, (uint32_t)zip->entry_compressed_size);
+		archive_le32enc(local_header + 22, (uint32_t)zip->entry_uncompressed_size);
+	}
+	archive_le16enc(local_header + 26, (uint16_t)filename_length);
+
+	if (zip->entry_encryption == ENCRYPTION_TRADITIONAL) {
+		if (zip->entry_flags & ZIP_ENTRY_FLAG_LENGTH_AT_END)
+			zip->trad_chkdat = local_header[11];
+		else
+			zip->trad_chkdat = local_header[17];
 	}
-	archive_le16enc(local_header + 26, filename_length);
 
 	/* Format as much of central directory file header as we can: */
 	zip->file_header = cd_alloc(zip, 46);
@@ -616,9 +810,14 @@ archive_write_zip_header(struct archive_write *a, struct archive_entry *entry)
 	archive_le16enc(zip->file_header + 4, 3 * 256 + version_needed);
 	archive_le16enc(zip->file_header + 6, version_needed);
 	archive_le16enc(zip->file_header + 8, zip->entry_flags);
-	archive_le16enc(zip->file_header + 10, zip->entry_compression);
-	archive_le32enc(zip->file_header + 12, dos_time(archive_entry_mtime(zip->entry)));
-	archive_le16enc(zip->file_header + 28, filename_length);
+	if (zip->entry_encryption == ENCRYPTION_WINZIP_AES128
+	    || zip->entry_encryption == ENCRYPTION_WINZIP_AES256)
+		archive_le16enc(zip->file_header + 10, WINZIP_AES_ENCRYPTION);
+	else
+		archive_le16enc(zip->file_header + 10, zip->entry_compression);
+	archive_le32enc(zip->file_header + 12,
+		dos_time(archive_entry_mtime(zip->entry)));
+	archive_le16enc(zip->file_header + 28, (uint16_t)filename_length);
 	/* Following Info-Zip, store mode in the "external attributes" field. */
 	archive_le32enc(zip->file_header + 38,
 	    archive_entry_mode(zip->entry) << 16);
@@ -670,7 +869,33 @@ archive_write_zip_header(struct archive_write *a, struct archive_entry *entry)
 	archive_le32enc(e, (uint32_t)archive_entry_gid(entry));
 	e += 4;
 
-	/* Copy UT and ux into central directory as well. */
+	/* AES extra data field: WinZIP AES information, ID=0x9901 */
+	if ((zip->entry_flags & ZIP_ENTRY_FLAG_ENCRYPTED)
+	    && (zip->entry_encryption == ENCRYPTION_WINZIP_AES128
+	        || zip->entry_encryption == ENCRYPTION_WINZIP_AES256)) {
+
+		memcpy(e, "\001\231\007\000\001\000AE", 8);
+		/* AES vendoer version AE-2 does not store a CRC.
+		 * WinZip 11 uses AE-1, which does store the CRC,
+		 * but it does not store the CRC when the file size
+		 * is less than 20 bytes. So we simulate what
+		 * WinZip 11 does.
+		 * NOTE: WinZip 9.0 and 10.0 uses AE-2 by default. */
+		if (archive_entry_size_is_set(zip->entry)
+		    && archive_entry_size(zip->entry) < 20) {
+			archive_le16enc(e+4, AES_VENDOR_AE_2);
+			zip->aes_vendor = AES_VENDOR_AE_2;/* no CRC. */
+		} else
+			zip->aes_vendor = AES_VENDOR_AE_1;
+		e += 8;
+		/* AES encryption strength. */
+		*e++ = (zip->entry_encryption == ENCRYPTION_WINZIP_AES128)?1:3;
+		/* Actual compression method. */
+		archive_le16enc(e, zip->entry_compression);
+		e += 2;
+	}
+
+	/* Copy UT ,ux, and AES-extra into central directory as well. */
 	zip->file_header_extra_offset = zip->central_directory_bytes;
 	cd_extra = cd_alloc(zip, e - local_extra);
 	memcpy(cd_extra, local_extra, e - local_extra);
@@ -692,14 +917,14 @@ archive_write_zip_header(struct archive_write *a, struct archive_entry *entry)
 		e += 8;
 		archive_le64enc(e, zip->entry_compressed_size);
 		e += 8;
-		archive_le16enc(zip64_start + 2, e - (zip64_start + 4));
+		archive_le16enc(zip64_start + 2, (uint16_t)(e - (zip64_start + 4)));
 	}
 
-	if (zip->flags & ZIP_FLAG_EXPERIMENT_EL) {
-		/* Experimental 'el' extension to improve streaming. */
+	if (zip->flags & ZIP_FLAG_EXPERIMENT_xl) {
+		/* Experimental 'xl' extension to improve streaming. */
 		unsigned char *external_info = e;
 		int included = 7;
-		memcpy(e, "el\000\000", 4); // 0x6c65 + 2-byte length
+		memcpy(e, "xl\000\000", 4); // 0x6c65 + 2-byte length
 		e += 4;
 		e[0] = included; /* bitmap of included fields */
 		e += 1;
@@ -720,11 +945,11 @@ archive_write_zip_header(struct archive_write *a, struct archive_entry *entry)
 		if (included & 8) {
 			// Libarchive does not currently support file comments.
 		}
-		archive_le16enc(external_info + 2, e - (external_info + 4));
+		archive_le16enc(external_info + 2, (uint16_t)(e - (external_info + 4)));
 	}
 
 	/* Update local header with size of extra data and write it all out: */
-	archive_le16enc(local_header + 28, e - local_extra);
+	archive_le16enc(local_header + 28, (uint16_t)(e - local_extra));
 
 	ret = __archive_write_output(a, local_header, 30);
 	if (ret != ARCHIVE_OK)
@@ -758,7 +983,7 @@ archive_write_zip_header(struct archive_write *a, struct archive_entry *entry)
 		zip->stream.opaque = Z_NULL;
 		zip->stream.next_out = zip->buf;
 		zip->stream.avail_out = (uInt)zip->len_buf;
-		if (deflateInit2(&zip->stream, Z_DEFAULT_COMPRESSION,
+		if (deflateInit2(&zip->stream, zip->deflate_compression_level,
 		    Z_DEFLATED, -15, 8, Z_DEFAULT_STRATEGY) != Z_OK) {
 			archive_set_error(&a->archive, ENOMEM,
 			    "Can't init deflate compressor");
@@ -782,13 +1007,72 @@ archive_write_zip_data(struct archive_write *a, const void *buff, size_t s)
 
 	if (s == 0) return 0;
 
+	if (zip->entry_flags & ZIP_ENTRY_FLAG_ENCRYPTED) {
+		switch (zip->entry_encryption) {
+		case ENCRYPTION_TRADITIONAL:
+			/* Initialize traditoinal PKWARE encryption context. */
+			if (!zip->tctx_valid) {
+				ret = init_traditional_pkware_encryption(a);
+				if (ret != ARCHIVE_OK)
+					return (ret);
+				zip->tctx_valid = 1;
+			}
+			break;
+		case ENCRYPTION_WINZIP_AES128:
+		case ENCRYPTION_WINZIP_AES256:
+			if (!zip->cctx_valid) {
+				ret = init_winzip_aes_encryption(a);
+				if (ret != ARCHIVE_OK)
+					return (ret);
+				zip->cctx_valid = zip->hctx_valid = 1;
+			}
+			break;
+		default:
+			break;
+		}
+	}
+
 	switch (zip->entry_compression) {
 	case COMPRESSION_STORE:
-		ret = __archive_write_output(a, buff, s);
-		if (ret != ARCHIVE_OK)
-			return (ret);
-		zip->written_bytes += s;
-		zip->entry_compressed_written += s;
+		if (zip->tctx_valid || zip->cctx_valid) {
+			const uint8_t *rb = (const uint8_t *)buff;
+			const uint8_t * const re = rb + s;
+
+			while (rb < re) {
+				size_t l;
+
+				if (zip->tctx_valid) {
+					l = trad_enc_encrypt_update(&zip->tctx,
+					    rb, re - rb,
+					    zip->buf, zip->len_buf);
+				} else {
+					l = zip->len_buf;
+					ret = archive_encrypto_aes_ctr_update(
+					    &zip->cctx,
+					    rb, re - rb, zip->buf, &l);
+					if (ret < 0) {
+						archive_set_error(&a->archive,
+						    ARCHIVE_ERRNO_MISC,
+						    "Failed to encrypt file");
+						return (ARCHIVE_FAILED);
+					}
+					archive_hmac_sha1_update(&zip->hctx,
+					    zip->buf, l);
+				}
+				ret = __archive_write_output(a, zip->buf, l);
+				if (ret != ARCHIVE_OK)
+					return (ret);
+				zip->entry_compressed_written += l;
+				zip->written_bytes += l;
+				rb += l;
+			}
+		} else {
+			ret = __archive_write_output(a, buff, s);
+			if (ret != ARCHIVE_OK)
+				return (ret);
+			zip->written_bytes += s;
+			zip->entry_compressed_written += s;
+		}
 		break;
 #if HAVE_ZLIB_H
 	case COMPRESSION_DEFLATE:
@@ -799,6 +1083,25 @@ archive_write_zip_data(struct archive_write *a, const void *buff, size_t s)
 			if (ret == Z_STREAM_ERROR)
 				return (ARCHIVE_FATAL);
 			if (zip->stream.avail_out == 0) {
+				if (zip->tctx_valid) {
+					trad_enc_encrypt_update(&zip->tctx,
+					    zip->buf, zip->len_buf,
+					    zip->buf, zip->len_buf);
+				} else if (zip->cctx_valid) {
+					size_t outl = zip->len_buf;
+					ret = archive_encrypto_aes_ctr_update(
+					    &zip->cctx,
+					    zip->buf, zip->len_buf,
+					    zip->buf, &outl);
+					if (ret < 0) {
+						archive_set_error(&a->archive,
+						    ARCHIVE_ERRNO_MISC,
+						    "Failed to encrypt file");
+						return (ARCHIVE_FAILED);
+					}
+					archive_hmac_sha1_update(&zip->hctx,
+					    zip->buf, zip->len_buf);
+				}
 				ret = __archive_write_output(a, zip->buf,
 					zip->len_buf);
 				if (ret != ARCHIVE_OK)
@@ -819,7 +1122,9 @@ archive_write_zip_data(struct archive_write *a, const void *buff, size_t s)
 	}
 
 	zip->entry_uncompressed_limit -= s;
-	zip->entry_crc32 = zip->crc32func(zip->entry_crc32, buff, (unsigned)s);
+	if (!zip->cctx_valid || zip->aes_vendor != AES_VENDOR_AE_2)
+		zip->entry_crc32 =
+		    zip->crc32func(zip->entry_crc32, buff, (unsigned)s);
 	return (s);
 
 }
@@ -834,10 +1139,28 @@ archive_write_zip_finish_entry(struct archive_write *a)
 	if (zip->entry_compression == COMPRESSION_DEFLATE) {
 		for (;;) {
 			size_t remainder;
+
 			ret = deflate(&zip->stream, Z_FINISH);
 			if (ret == Z_STREAM_ERROR)
 				return (ARCHIVE_FATAL);
 			remainder = zip->len_buf - zip->stream.avail_out;
+			if (zip->tctx_valid) {
+				trad_enc_encrypt_update(&zip->tctx,
+				    zip->buf, remainder, zip->buf, remainder);
+			} else if (zip->cctx_valid) {
+				size_t outl = remainder;
+				ret = archive_encrypto_aes_ctr_update(
+				    &zip->cctx, zip->buf, remainder,
+				    zip->buf, &outl);
+				if (ret < 0) {
+					archive_set_error(&a->archive,
+					    ARCHIVE_ERRNO_MISC,
+					    "Failed to encrypt file");
+					return (ARCHIVE_FAILED);
+				}
+				archive_hmac_sha1_update(&zip->hctx,
+				    zip->buf, remainder);
+			}
 			ret = __archive_write_output(a, zip->buf, remainder);
 			if (ret != ARCHIVE_OK)
 				return (ret);
@@ -851,20 +1174,38 @@ archive_write_zip_finish_entry(struct archive_write *a)
 		deflateEnd(&zip->stream);
 	}
 #endif
+	if (zip->hctx_valid) {
+		uint8_t hmac[20];
+		size_t hmac_len = 20;
+
+		archive_hmac_sha1_final(&zip->hctx, hmac, &hmac_len);
+		ret = __archive_write_output(a, hmac, AUTH_CODE_SIZE);
+		if (ret != ARCHIVE_OK)
+			return (ret);
+		zip->entry_compressed_written += AUTH_CODE_SIZE;
+		zip->written_bytes += AUTH_CODE_SIZE;
+	}
 
 	/* Write trailing data descriptor. */
 	if ((zip->entry_flags & ZIP_ENTRY_FLAG_LENGTH_AT_END) != 0) {
 		char d[24];
 		memcpy(d, "PK\007\010", 4);
-		archive_le32enc(d + 4, zip->entry_crc32);
+		if (zip->cctx_valid && zip->aes_vendor == AES_VENDOR_AE_2)
+			archive_le32enc(d + 4, 0);/* no CRC.*/
+		else
+			archive_le32enc(d + 4, zip->entry_crc32);
 		if (zip->entry_uses_zip64) {
-			archive_le64enc(d + 8, (uint64_t)zip->entry_compressed_written);
-			archive_le64enc(d + 16, (uint64_t)zip->entry_uncompressed_written);
+			archive_le64enc(d + 8,
+				(uint64_t)zip->entry_compressed_written);
+			archive_le64enc(d + 16,
+				(uint64_t)zip->entry_uncompressed_written);
 			ret = __archive_write_output(a, d, 24);
 			zip->written_bytes += 24;
 		} else {
-			archive_le32enc(d + 8, (uint32_t)zip->entry_compressed_written);
-			archive_le32enc(d + 12, (uint32_t)zip->entry_uncompressed_written);
+			archive_le32enc(d + 8,
+				(uint32_t)zip->entry_compressed_written);
+			archive_le32enc(d + 12,
+				(uint32_t)zip->entry_uncompressed_written);
 			ret = __archive_write_output(a, d, 16);
 			zip->written_bytes += 16;
 		}
@@ -892,7 +1233,7 @@ archive_write_zip_finish_entry(struct archive_write *a)
 			archive_le64enc(z, zip->entry_offset);
 			z += 8;
 		}
-		archive_le16enc(zip64 + 2, z - (zip64 + 4));
+		archive_le16enc(zip64 + 2, (uint16_t)(z - (zip64 + 4)));
 		zd = cd_alloc(zip, z - zip64);
 		if (zd == NULL) {
 			archive_set_error(&a->archive, ENOMEM,
@@ -906,15 +1247,21 @@ archive_write_zip_finish_entry(struct archive_write *a)
 	}
 
 	/* Fix up central directory file header. */
-	archive_le32enc(zip->file_header + 16, zip->entry_crc32);
+	if (zip->cctx_valid && zip->aes_vendor == AES_VENDOR_AE_2)
+		archive_le32enc(zip->file_header + 16, 0);/* no CRC.*/
+	else
+		archive_le32enc(zip->file_header + 16, zip->entry_crc32);
 	archive_le32enc(zip->file_header + 20,
-	    zipmin(zip->entry_compressed_written, 0xffffffffLL));
+		(uint32_t)zipmin(zip->entry_compressed_written,
+				 ARCHIVE_LITERAL_LL(0xffffffff)));
 	archive_le32enc(zip->file_header + 24,
-	    zipmin(zip->entry_uncompressed_written, 0xffffffffLL));
+		(uint32_t)zipmin(zip->entry_uncompressed_written,
+				 ARCHIVE_LITERAL_LL(0xffffffff)));
 	archive_le16enc(zip->file_header + 30,
-	    zip->central_directory_bytes - zip->file_header_extra_offset);
+	    (uint16_t)(zip->central_directory_bytes - zip->file_header_extra_offset));
 	archive_le32enc(zip->file_header + 42,
-	    zipmin(zip->entry_offset, 0xffffffffLL));
+		(uint32_t)zipmin(zip->entry_offset,
+				 ARCHIVE_LITERAL_LL(0xffffffff)));
 
 	return (ARCHIVE_OK);
 }
@@ -941,8 +1288,8 @@ archive_write_zip_close(struct archive_write *a)
 	offset_end = zip->written_bytes;
 
 	/* If central dir info is too large, write Zip64 end-of-cd */
-	if (offset_end - offset_start > 0xffffffffLL
-	    || offset_start > 0xffffffffLL
+	if (offset_end - offset_start > ARCHIVE_LITERAL_LL(0xffffffff)
+	    || offset_start > ARCHIVE_LITERAL_LL(0xffffffff)
 	    || zip->central_directory_entries > 0xffffUL
 	    || (zip->flags & ZIP_FLAG_FORCE_ZIP64)) {
 	  /* Zip64 end-of-cd record */
@@ -977,10 +1324,14 @@ archive_write_zip_close(struct archive_write *a)
 	/* Format and write end of central directory. */
 	memset(buff, 0, sizeof(buff));
 	memcpy(buff, "PK\005\006", 4);
-	archive_le16enc(buff + 8, zipmin(0xffffU, zip->central_directory_entries));
-	archive_le16enc(buff + 10, zipmin(0xffffU, zip->central_directory_entries));
-	archive_le32enc(buff + 12, (uint32_t)zipmin(0xffffffffLL, (offset_end - offset_start)));
-	archive_le32enc(buff + 16, (uint32_t)zipmin(0xffffffffLL, offset_start));
+	archive_le16enc(buff + 8, (uint16_t)zipmin(0xffffU,
+		zip->central_directory_entries));
+	archive_le16enc(buff + 10, (uint16_t)zipmin(0xffffU,
+		zip->central_directory_entries));
+	archive_le32enc(buff + 12,
+		(uint32_t)zipmin(0xffffffffLL, (offset_end - offset_start)));
+	archive_le32enc(buff + 16,
+		(uint32_t)zipmin(0xffffffffLL, offset_start));
 	ret = __archive_write_output(a, buff, 22);
 	if (ret != ARCHIVE_OK)
 		return (ARCHIVE_FATAL);
@@ -1001,10 +1352,12 @@ archive_write_zip_free(struct archive_write *a)
 		free(segment->buff);
 		free(segment);
 	}
-#ifdef HAVE_ZLIB_H
 	free(zip->buf);
-#endif
 	archive_entry_free(zip->entry);
+	if (zip->cctx_valid)
+		archive_encrypto_aes_ctr_release(&zip->cctx);
+	if (zip->hctx_valid)
+		archive_hmac_sha1_cleanup(&zip->hctx);
 	/* TODO: Free opt_sconv, sconv_default */
 
 	free(zip);
@@ -1124,3 +1477,199 @@ get_sconv(struct archive_write *a, struct zip *zip)
 	}
 	return (zip->sconv_default);
 }
+
+/*
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
+static unsigned
+trad_enc_encrypt_update(struct trad_enc_ctx *ctx, const uint8_t *in,
+    size_t in_len, uint8_t *out, size_t out_len)
+{
+	unsigned i, max;
+
+	max = (unsigned)((in_len < out_len)? in_len: out_len);
+
+	for (i = 0; i < max; i++) {
+		uint8_t t = in[i];
+		out[i] = t ^ trad_enc_decypt_byte(ctx);
+		trad_enc_update_keys(ctx, t);
+	}
+	return i;
+}
+
+static int
+trad_enc_init(struct trad_enc_ctx *ctx, const char *pw, size_t pw_len)
+{
+
+	ctx->keys[0] = 305419896L;
+	ctx->keys[1] = 591751049L;
+	ctx->keys[2] = 878082192L;
+
+	for (;pw_len; --pw_len)
+		trad_enc_update_keys(ctx, *pw++);
+	return 0;
+}
+
+static int
+is_traditional_pkware_encryption_supported(void)
+{
+	uint8_t key[TRAD_HEADER_SIZE];
+
+	if (archive_random(key, sizeof(key)-1) != ARCHIVE_OK)
+		return (0);
+	return (1);
+}
+
+static int
+init_traditional_pkware_encryption(struct archive_write *a)
+{
+	struct zip *zip = a->format_data;
+	const char *passphrase;
+	uint8_t key[TRAD_HEADER_SIZE];
+	uint8_t key_encrypted[TRAD_HEADER_SIZE];
+	int ret;
+
+	passphrase = __archive_write_get_passphrase(a);
+	if (passphrase == NULL) {
+		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+		    "Encryption needs passphrase");
+		return ARCHIVE_FAILED;
+	}
+	if (archive_random(key, sizeof(key)-1) != ARCHIVE_OK) {
+		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+		    "Can't generate random number for encryption");
+		return ARCHIVE_FATAL;
+	}
+	trad_enc_init(&zip->tctx, passphrase, strlen(passphrase));
+	/* Set the last key code which will be used as a check code
+	 * for verifying passphrase in decryption. */
+	key[TRAD_HEADER_SIZE-1] = zip->trad_chkdat;
+	trad_enc_encrypt_update(&zip->tctx, key, TRAD_HEADER_SIZE,
+	    key_encrypted, TRAD_HEADER_SIZE);
+	/* Write encrypted keys in the top of the file content. */
+	ret = __archive_write_output(a, key_encrypted, TRAD_HEADER_SIZE);
+	if (ret != ARCHIVE_OK)
+		return (ret);
+	zip->written_bytes += TRAD_HEADER_SIZE;
+	zip->entry_compressed_written += TRAD_HEADER_SIZE;
+	return (ret);
+}
+
+static int
+init_winzip_aes_encryption(struct archive_write *a)
+{
+	struct zip *zip = a->format_data;
+	const char *passphrase;
+	size_t key_len, salt_len;
+	uint8_t salt[16 + 2];
+	uint8_t derived_key[MAX_DERIVED_KEY_BUF_SIZE];
+	int ret;
+
+	passphrase = __archive_write_get_passphrase(a);
+	if (passphrase == NULL) {
+		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+		    "Encryption needs passphrase");
+		return (ARCHIVE_FAILED);
+	}
+	if (zip->entry_encryption == ENCRYPTION_WINZIP_AES128) {
+		salt_len = 8;
+		key_len = 16;
+	} else {
+		/* AES 256 */
+		salt_len = 16;
+		key_len = 32;
+	}
+	if (archive_random(salt, salt_len) != ARCHIVE_OK) {
+		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+		    "Can't generate random number for encryption");
+		return (ARCHIVE_FATAL);
+	}
+	archive_pbkdf2_sha1(passphrase, strlen(passphrase),
+	    salt, salt_len, 1000, derived_key, key_len * 2 + 2);
+
+	ret = archive_encrypto_aes_ctr_init(&zip->cctx, derived_key, key_len);
+	if (ret != 0) {
+		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+		    "Decryption is unsupported due to lack of crypto library");
+		return (ARCHIVE_FAILED);
+	}
+	ret = archive_hmac_sha1_init(&zip->hctx, derived_key + key_len,
+	    key_len);
+	if (ret != 0) {
+		archive_encrypto_aes_ctr_release(&zip->cctx);
+		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+		    "Failed to initialize HMAC-SHA1");
+		return (ARCHIVE_FAILED);
+        }
+
+	/* Set a passowrd verification value after the 'salt'. */
+	salt[salt_len] = derived_key[key_len * 2];
+	salt[salt_len + 1] = derived_key[key_len * 2 + 1];
+
+	/* Write encrypted keys in the top of the file content. */
+	ret = __archive_write_output(a, salt, salt_len + 2);
+	if (ret != ARCHIVE_OK)
+		return (ret);
+	zip->written_bytes += salt_len + 2;
+	zip->entry_compressed_written += salt_len + 2;
+
+	return (ARCHIVE_OK);
+}
+
+static int
+is_winzip_aes_encryption_supported(int encryption)
+{
+	size_t key_len, salt_len;
+	uint8_t salt[16 + 2];
+	uint8_t derived_key[MAX_DERIVED_KEY_BUF_SIZE];
+	archive_crypto_ctx cctx;
+	archive_hmac_sha1_ctx hctx;
+	int ret;
+
+	if (encryption == ENCRYPTION_WINZIP_AES128) {
+		salt_len = 8;
+		key_len = 16;
+	} else {
+		/* AES 256 */
+		salt_len = 16;
+		key_len = 32;
+	}
+	if (archive_random(salt, salt_len) != ARCHIVE_OK)
+		return (0);
+	ret = archive_pbkdf2_sha1("p", 1, salt, salt_len, 1000,
+	    derived_key, key_len * 2 + 2);
+	if (ret != 0)
+		return (0);
+
+	ret = archive_encrypto_aes_ctr_init(&cctx, derived_key, key_len);
+	if (ret != 0)
+		return (0);
+	ret = archive_hmac_sha1_init(&hctx, derived_key + key_len,
+	    key_len);
+	archive_encrypto_aes_ctr_release(&cctx);
+	if (ret != 0)
+		return (0);
+	archive_hmac_sha1_cleanup(&hctx);
+	return (1);
+}