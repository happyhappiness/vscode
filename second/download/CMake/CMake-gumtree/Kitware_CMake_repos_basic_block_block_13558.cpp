{
		const char *p;
		ssize_t grabbing_bytes = 24;

		if (zip->hctx_valid)
			grabbing_bytes += AUTH_CODE_SIZE;
		/* Grab at least 24 bytes. */
		buff = __archive_read_ahead(a, grabbing_bytes, &bytes_avail);
		if (bytes_avail < grabbing_bytes) {
			/* Zip archives have end-of-archive markers
			   that are longer than this, so a failure to get at
			   least 24 bytes really does indicate a truncated
			   file. */
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Truncated ZIP file data");
			return (ARCHIVE_FATAL);
		}
		/* Check for a complete PK\007\010 signature, followed
		 * by the correct 4-byte CRC. */
		p = buff;
		if (zip->hctx_valid)
			p += AUTH_CODE_SIZE;
		if (p[0] == 'P' && p[1] == 'K'
		    && p[2] == '\007' && p[3] == '\010'
		    && (archive_le32dec(p + 4) == zip->entry_crc32
			|| zip->ignore_crc32
			|| (zip->hctx_valid
			 && zip->entry->aes_extra.vendor == AES_VENDOR_AE_2))) {
			if (zip->entry->flags & LA_USED_ZIP64) {
				uint64_t compressed, uncompressed;
				zip->entry->crc32 = archive_le32dec(p + 4);
				compressed = archive_le64dec(p + 8);
				uncompressed = archive_le64dec(p + 16);
				if (compressed > INT64_MAX || uncompressed > INT64_MAX) {
					archive_set_error(&a->archive,
					    ARCHIVE_ERRNO_FILE_FORMAT,
					    "Overflow of 64-bit file sizes");
					return ARCHIVE_FAILED;
				}
				zip->entry->compressed_size = compressed;
				zip->entry->uncompressed_size = uncompressed;
				zip->unconsumed = 24;
			} else {
				zip->entry->crc32 = archive_le32dec(p + 4);
				zip->entry->compressed_size =
					archive_le32dec(p + 8);
				zip->entry->uncompressed_size =
					archive_le32dec(p + 12);
				zip->unconsumed = 16;
			}
			if (zip->hctx_valid) {
				r = check_authentication_code(a, buff);
				if (r != ARCHIVE_OK)
					return (r);
			}
			zip->end_of_entry = 1;
			return (ARCHIVE_OK);
		}
		/* If not at EOF, ensure we consume at least one byte. */
		++p;

		/* Scan forward until we see where a PK\007\010 signature
		 * might be. */
		/* Return bytes up until that point.  On the next call,
		 * the code above will verify the data descriptor. */
		while (p < buff + bytes_avail - 4) {
			if (p[3] == 'P') { p += 3; }
			else if (p[3] == 'K') { p += 2; }
			else if (p[3] == '\007') { p += 1; }
			else if (p[3] == '\010' && p[2] == '\007'
			    && p[1] == 'K' && p[0] == 'P') {
				if (zip->hctx_valid)
					p -= AUTH_CODE_SIZE;
				break;
			} else { p += 4; }
		}
		bytes_avail = p - buff;
	}