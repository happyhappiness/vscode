@@ -199,7 +199,7 @@ struct zip {
 	struct trad_enc_ctx	tctx;
 	char			tctx_valid;
 
-	/* WinZip AES decyption. */
+	/* WinZip AES decryption. */
 	/* Contexts used for AES decryption. */
 	archive_crypto_ctx	cctx;
 	char			cctx_valid;
@@ -242,7 +242,7 @@ trad_enc_update_keys(struct trad_enc_ctx *ctx, uint8_t c)
 }
 
 static uint8_t
-trad_enc_decypt_byte(struct trad_enc_ctx *ctx)
+trad_enc_decrypt_byte(struct trad_enc_ctx *ctx)
 {
 	unsigned temp = ctx->keys[2] | 2;
 	return (uint8_t)((temp * (temp ^ 1)) >> 8) & 0xff;
@@ -257,7 +257,7 @@ trad_enc_decrypt_update(struct trad_enc_ctx *ctx, const uint8_t *in,
 	max = (unsigned)((in_len < out_len)? in_len: out_len);
 
 	for (i = 0; i < max; i++) {
-		uint8_t t = in[i] ^ trad_enc_decypt_byte(ctx);
+		uint8_t t = in[i] ^ trad_enc_decrypt_byte(ctx);
 		out[i] = t;
 		trad_enc_update_keys(ctx, t);
 	}
@@ -418,18 +418,30 @@ zip_time(const char *p)
  *	id1+size1+data1 + id2+size2+data2 ...
  *  triplets.  id and size are 2 bytes each.
  */
-static void
-process_extra(const char *p, size_t extra_length, struct zip_entry* zip_entry)
+static int
+process_extra(struct archive_read *a, const char *p, size_t extra_length, struct zip_entry* zip_entry)
 {
 	unsigned offset = 0;
 
-	while (offset < extra_length - 4) {
+	if (extra_length == 0) {
+		return ARCHIVE_OK;
+	}
+
+	if (extra_length < 4) {
+		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+		    "Too-small extra data: Need at least 4 bytes, but only found %d bytes", (int)extra_length);
+		return ARCHIVE_FAILED;
+	}
+	while (offset <= extra_length - 4) {
 		unsigned short headerid = archive_le16dec(p + offset);
 		unsigned short datasize = archive_le16dec(p + offset + 2);
 
 		offset += 4;
 		if (offset + datasize > extra_length) {
-			break;
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+			    "Extra data overflow: Need %d bytes but only found %d bytes",
+			    (int)datasize, (int)(extra_length - offset));
+			return ARCHIVE_FAILED;
 		}
 #ifdef DEBUG
 		fprintf(stderr, "Header id 0x%04x, length %d\n",
@@ -440,26 +452,38 @@ process_extra(const char *p, size_t extra_length, struct zip_entry* zip_entry)
 			/* Zip64 extended information extra field. */
 			zip_entry->flags |= LA_USED_ZIP64;
 			if (zip_entry->uncompressed_size == 0xffffffff) {
-				if (datasize < 8)
-					break;
-				zip_entry->uncompressed_size =
-				    archive_le64dec(p + offset);
+				uint64_t t = 0;
+				if (datasize < 8
+				    || (t = archive_le64dec(p + offset)) > INT64_MAX) {
+					archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+					    "Malformed 64-bit uncompressed size");
+					return ARCHIVE_FAILED;
+				}
+				zip_entry->uncompressed_size = t;
 				offset += 8;
 				datasize -= 8;
 			}
 			if (zip_entry->compressed_size == 0xffffffff) {
-				if (datasize < 8)
-					break;
-				zip_entry->compressed_size =
-				    archive_le64dec(p + offset);
+				uint64_t t = 0;
+				if (datasize < 8
+				    || (t = archive_le64dec(p + offset)) > INT64_MAX) {
+					archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+					    "Malformed 64-bit compressed size");
+					return ARCHIVE_FAILED;
+				}
+				zip_entry->compressed_size = t;
 				offset += 8;
 				datasize -= 8;
 			}
 			if (zip_entry->local_header_offset == 0xffffffff) {
-				if (datasize < 8)
-					break;
-				zip_entry->local_header_offset =
-				    archive_le64dec(p + offset);
+				uint64_t t = 0;
+				if (datasize < 8
+				    || (t = archive_le64dec(p + offset)) > INT64_MAX) {
+					archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+					    "Malformed 64-bit local header offset");
+					return ARCHIVE_FAILED;
+				}
+				zip_entry->local_header_offset = t;
 				offset += 8;
 				datasize -= 8;
 			}
@@ -698,7 +722,7 @@ process_extra(const char *p, size_t extra_length, struct zip_entry* zip_entry)
 			break;
 		}
 		case 0x9901:
-			/* WinZIp AES extra data field. */
+			/* WinZip AES extra data field. */
 			if (p[offset + 2] == 'A' && p[offset + 3] == 'E') {
 				/* Vendor version. */
 				zip_entry->aes_extra.vendor =
@@ -715,13 +739,13 @@ process_extra(const char *p, size_t extra_length, struct zip_entry* zip_entry)
 		}
 		offset += datasize;
 	}
-#ifdef DEBUG
-	if (offset != extra_length)
-	{
-		fprintf(stderr,
-		    "Extra data field contents do not match reported size!\n");
+	if (offset != extra_length) {
+		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+		    "Malformed extra data: Consumed %d bytes of %d bytes",
+		    (int)offset, (int)extra_length);
+		return ARCHIVE_FAILED;
 	}
-#endif
+	return ARCHIVE_OK;
 }
 
 /*
@@ -840,7 +864,9 @@ zip_read_local_file_header(struct archive_read *a, struct archive_entry *entry,
 		return (ARCHIVE_FATAL);
 	}
 
-	process_extra(h, extra_length, zip_entry);
+	if (ARCHIVE_OK != process_extra(a, h, extra_length, zip_entry)) {
+		return ARCHIVE_FATAL;
+	}
 	__archive_read_consume(a, extra_length);
 
 	/* Work around a bug in Info-Zip: When reading from a pipe, it
@@ -850,29 +876,33 @@ zip_read_local_file_header(struct archive_read *a, struct archive_entry *entry,
 		zip_entry->mode |= AE_IFREG;
 	}
 
-	if ((zip_entry->mode & AE_IFMT) == 0) {
-		/* Especially in streaming mode, we can end up
-		   here without having seen proper mode information.
-		   Guess from the filename. */
+	/* If the mode is totally empty, set some sane default. */
+	if (zip_entry->mode == 0) {
+		zip_entry->mode |= 0664;
+	}
+
+	/* Make sure that entries with a trailing '/' are marked as directories
+	 * even if the External File Attributes contains bogus values.  If this
+	 * is not a directory and there is no type, assume regularfile. */
+	if ((zip_entry->mode & AE_IFMT) != AE_IFDIR) {
+		int has_slash;
+
 		wp = archive_entry_pathname_w(entry);
 		if (wp != NULL) {
 			len = wcslen(wp);
-			if (len > 0 && wp[len - 1] == L'/')
-				zip_entry->mode |= AE_IFDIR;
-			else
-				zip_entry->mode |= AE_IFREG;
+			has_slash = len > 0 && wp[len - 1] == L'/';
 		} else {
 			cp = archive_entry_pathname(entry);
 			len = (cp != NULL)?strlen(cp):0;
-			if (len > 0 && cp[len - 1] == '/')
-				zip_entry->mode |= AE_IFDIR;
-			else
-				zip_entry->mode |= AE_IFREG;
+			has_slash = len > 0 && cp[len - 1] == '/';
 		}
-		if (zip_entry->mode == AE_IFDIR) {
-			zip_entry->mode |= 0775;
-		} else if (zip_entry->mode == AE_IFREG) {
-			zip_entry->mode |= 0664;
+		/* Correct file type as needed. */
+		if (has_slash) {
+			zip_entry->mode &= ~AE_IFMT;
+			zip_entry->mode |= AE_IFDIR;
+			zip_entry->mode |= 0111;
+		} else if ((zip_entry->mode & AE_IFMT) == 0) {
+			zip_entry->mode |= AE_IFREG;
 		}
 	}
 
@@ -887,6 +917,7 @@ zip_read_local_file_header(struct archive_read *a, struct archive_entry *entry,
 				archive_wstrcat(&s, wp);
 				archive_wstrappend_wchar(&s, L'/');
 				archive_entry_copy_pathname_w(entry, s.s);
+				archive_wstring_free(&s);
 			}
 		} else {
 			cp = archive_entry_pathname(entry);
@@ -897,6 +928,7 @@ zip_read_local_file_header(struct archive_read *a, struct archive_entry *entry,
 				archive_strcat(&s, cp);
 				archive_strappend_char(&s, '/');
 				archive_entry_set_pathname(entry, s.s);
+				archive_string_free(&s);
 			}
 		}
 	}
@@ -1136,11 +1168,18 @@ zip_read_data_none(struct archive_read *a, const void **_buff,
 			|| (zip->hctx_valid
 			 && zip->entry->aes_extra.vendor == AES_VENDOR_AE_2))) {
 			if (zip->entry->flags & LA_USED_ZIP64) {
+				uint64_t compressed, uncompressed;
 				zip->entry->crc32 = archive_le32dec(p + 4);
-				zip->entry->compressed_size =
-					archive_le64dec(p + 8);
-				zip->entry->uncompressed_size =
-					archive_le64dec(p + 16);
+				compressed = archive_le64dec(p + 8);
+				uncompressed = archive_le64dec(p + 16);
+				if (compressed > INT64_MAX || uncompressed > INT64_MAX) {
+					archive_set_error(&a->archive,
+					    ARCHIVE_ERRNO_FILE_FORMAT,
+					    "Overflow of 64-bit file sizes");
+					return ARCHIVE_FAILED;
+				}
+				zip->entry->compressed_size = compressed;
+				zip->entry->uncompressed_size = uncompressed;
 				zip->unconsumed = 24;
 			} else {
 				zip->entry->crc32 = archive_le32dec(p + 4);
@@ -1293,7 +1332,7 @@ zip_read_data_deflate(struct archive_read *a, const void **buff,
 	    && bytes_avail > zip->entry_bytes_remaining) {
 		bytes_avail = (ssize_t)zip->entry_bytes_remaining;
 	}
-	if (bytes_avail <= 0) {
+	if (bytes_avail < 0) {
 		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
 		    "Truncated ZIP file body");
 		return (ARCHIVE_FATAL);
@@ -1417,9 +1456,18 @@ zip_read_data_deflate(struct archive_read *a, const void **buff,
 			zip->unconsumed = 4;
 		}
 		if (zip->entry->flags & LA_USED_ZIP64) {
+			uint64_t compressed, uncompressed;
 			zip->entry->crc32 = archive_le32dec(p);
-			zip->entry->compressed_size = archive_le64dec(p + 4);
-			zip->entry->uncompressed_size = archive_le64dec(p + 12);
+			compressed = archive_le64dec(p + 4);
+			uncompressed = archive_le64dec(p + 12);
+			if (compressed > INT64_MAX || uncompressed > INT64_MAX) {
+				archive_set_error(&a->archive,
+				    ARCHIVE_ERRNO_FILE_FORMAT,
+				    "Overflow of 64-bit file sizes");
+				return ARCHIVE_FAILED;
+			}
+			zip->entry->compressed_size = compressed;
+			zip->entry->uncompressed_size = uncompressed;
 			zip->unconsumed += 20;
 		} else {
 			zip->entry->crc32 = archive_le32dec(p);
@@ -1500,7 +1548,7 @@ read_decryption_header(struct archive_read *a)
 	case 0x6720:/* Blowfish */
 	case 0x6721:/* Twofish */
 	case 0x6801:/* RC4 */
-		/* Suuported encryption algorithm. */
+		/* Supported encryption algorithm. */
 		break;
 	default:
 		archive_set_error(&a->archive,
@@ -1609,7 +1657,7 @@ read_decryption_header(struct archive_read *a)
 	__archive_read_consume(a, 4);
 
 	/*return (ARCHIVE_OK);
-	 * This is not fully implemnted yet.*/
+	 * This is not fully implemented yet.*/
 	archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
 	    "Encrypted file is unsupported");
 	return (ARCHIVE_FAILED);
@@ -1691,7 +1739,7 @@ init_traditional_PKWARE_decryption(struct archive_read *a)
 		}
 
 		/*
-		 * Initialize ctx for Traditional PKWARE Decyption.
+		 * Initialize ctx for Traditional PKWARE Decryption.
 		 */
 		r = trad_enc_init(&zip->tctx, passphrase, strlen(passphrase),
 			p, ENC_HEADER_SIZE, &crcchk);
@@ -2691,7 +2739,9 @@ slurp_central_directory(struct archive_read *a, struct zip *zip)
 			    "Truncated ZIP file header");
 			return ARCHIVE_FATAL;
 		}
-		process_extra(p + filename_length, extra_length, zip_entry);
+		if (ARCHIVE_OK != process_extra(a, p + filename_length, extra_length, zip_entry)) {
+			return ARCHIVE_FATAL;
+		}
 
 		/*
 		 * Mac resource fork files are stored under the