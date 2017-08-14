static int
archive_write_zip_finish_entry(struct archive_write *a)
{
	struct zip *zip = a->format_data;
	int ret;

#if HAVE_ZLIB_H
	if (zip->entry_compression == COMPRESSION_DEFLATE) {
		for (;;) {
			size_t remainder;

			ret = deflate(&zip->stream, Z_FINISH);
			if (ret == Z_STREAM_ERROR)
				return (ARCHIVE_FATAL);
			remainder = zip->len_buf - zip->stream.avail_out;
			if (zip->tctx_valid) {
				trad_enc_encrypt_update(&zip->tctx,
				    zip->buf, remainder, zip->buf, remainder);
			} else if (zip->cctx_valid) {
				size_t outl = remainder;
				ret = archive_encrypto_aes_ctr_update(
				    &zip->cctx, zip->buf, remainder,
				    zip->buf, &outl);
				if (ret < 0) {
					archive_set_error(&a->archive,
					    ARCHIVE_ERRNO_MISC,
					    "Failed to encrypt file");
					return (ARCHIVE_FAILED);
				}
				archive_hmac_sha1_update(&zip->hctx,
				    zip->buf, remainder);
			}
			ret = __archive_write_output(a, zip->buf, remainder);
			if (ret != ARCHIVE_OK)
				return (ret);
			zip->entry_compressed_written += remainder;
			zip->written_bytes += remainder;
			zip->stream.next_out = zip->buf;
			if (zip->stream.avail_out != 0)
				break;
			zip->stream.avail_out = (uInt)zip->len_buf;
		}
		deflateEnd(&zip->stream);
	}
#endif
	if (zip->hctx_valid) {
		uint8_t hmac[20];
		size_t hmac_len = 20;

		archive_hmac_sha1_final(&zip->hctx, hmac, &hmac_len);
		ret = __archive_write_output(a, hmac, AUTH_CODE_SIZE);
		if (ret != ARCHIVE_OK)
			return (ret);
		zip->entry_compressed_written += AUTH_CODE_SIZE;
		zip->written_bytes += AUTH_CODE_SIZE;
	}

	/* Write trailing data descriptor. */
	if ((zip->entry_flags & ZIP_ENTRY_FLAG_LENGTH_AT_END) != 0) {
		char d[24];
		memcpy(d, "PK\007\010", 4);
		if (zip->cctx_valid && zip->aes_vendor == AES_VENDOR_AE_2)
			archive_le32enc(d + 4, 0);/* no CRC.*/
		else
			archive_le32enc(d + 4, zip->entry_crc32);
		if (zip->entry_uses_zip64) {
			archive_le64enc(d + 8,
				(uint64_t)zip->entry_compressed_written);
			archive_le64enc(d + 16,
				(uint64_t)zip->entry_uncompressed_written);
			ret = __archive_write_output(a, d, 24);
			zip->written_bytes += 24;
		} else {
			archive_le32enc(d + 8,
				(uint32_t)zip->entry_compressed_written);
			archive_le32enc(d + 12,
				(uint32_t)zip->entry_uncompressed_written);
			ret = __archive_write_output(a, d, 16);
			zip->written_bytes += 16;
		}
		if (ret != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
	}

	/* Append Zip64 extra data to central directory information. */
	if (zip->entry_compressed_written > ZIP_4GB_MAX
	    || zip->entry_uncompressed_written > ZIP_4GB_MAX
	    || zip->entry_offset > ZIP_4GB_MAX) {
		unsigned char zip64[32];
		unsigned char *z = zip64, *zd;
		memcpy(z, "\001\000\000\000", 4);
		z += 4;
		if (zip->entry_uncompressed_written >= ZIP_4GB_MAX) {
			archive_le64enc(z, zip->entry_uncompressed_written);
			z += 8;
		}
		if (zip->entry_compressed_written >= ZIP_4GB_MAX) {
			archive_le64enc(z, zip->entry_compressed_written);
			z += 8;
		}
		if (zip->entry_offset >= ZIP_4GB_MAX) {
			archive_le64enc(z, zip->entry_offset);
			z += 8;
		}
		archive_le16enc(zip64 + 2, (uint16_t)(z - (zip64 + 4)));
		zd = cd_alloc(zip, z - zip64);
		if (zd == NULL) {
			archive_set_error(&a->archive, ENOMEM,
				"Can't allocate zip data");
			return (ARCHIVE_FATAL);
		}
		memcpy(zd, zip64, z - zip64);
		/* Zip64 means version needs to be set to at least 4.5 */
		if (archive_le16dec(zip->file_header + 6) < 45)
			archive_le16enc(zip->file_header + 6, 45);
	}

	/* Fix up central directory file header. */
	if (zip->cctx_valid && zip->aes_vendor == AES_VENDOR_AE_2)
		archive_le32enc(zip->file_header + 16, 0);/* no CRC.*/
	else
		archive_le32enc(zip->file_header + 16, zip->entry_crc32);
	archive_le32enc(zip->file_header + 20,
		(uint32_t)zipmin(zip->entry_compressed_written,
				 ZIP_4GB_MAX));
	archive_le32enc(zip->file_header + 24,
		(uint32_t)zipmin(zip->entry_uncompressed_written,
				 ZIP_4GB_MAX));
	archive_le16enc(zip->file_header + 30,
	    (uint16_t)(zip->central_directory_bytes - zip->file_header_extra_offset));
	archive_le32enc(zip->file_header + 42,
		(uint32_t)zipmin(zip->entry_offset,
				 ZIP_4GB_MAX));

	return (ARCHIVE_OK);
}