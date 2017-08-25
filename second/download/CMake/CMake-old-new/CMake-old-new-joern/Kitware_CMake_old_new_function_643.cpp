static int
slurp_central_directory(struct archive_read *a, struct _7zip *zip,
    struct _7z_header_info *header)
{
	const unsigned char *p;
	const void *image;
	uint64_t len;
	uint64_t next_header_offset;
	uint64_t next_header_size;
	uint32_t next_header_crc;
	ssize_t bytes_avail, image_bytes;
	int r;

	if ((p = __archive_read_ahead(a, 32, &bytes_avail)) == NULL)
		return (ARCHIVE_FATAL);

	if ((p[0] == 'M' && p[1] == 'Z') || memcmp(p, "\x7F\x45LF", 4) == 0) {
		/* This is an executable ? Must be self-extracting... */
		r = skip_sfx(a, bytes_avail);
		if (r < ARCHIVE_WARN)
			return (r);
		if ((p = __archive_read_ahead(a, 32, NULL)) == NULL)
			return (ARCHIVE_FATAL);
	}
	zip->seek_base += 32;

	if (memcmp(p, _7ZIP_SIGNATURE, 6) != 0) {
		archive_set_error(&a->archive, -1, "Not 7-Zip archive file");
		return (ARCHIVE_FATAL);
	}

	/* CRC check. */
	if (crc32(0, (unsigned char *)p + 12, 20) != archive_le32dec(p + 8)) {
		archive_set_error(&a->archive, -1, "Header CRC error");
		return (ARCHIVE_FATAL);
	}

	next_header_offset = archive_le64dec(p + 12);
	next_header_size = archive_le64dec(p + 20);
	next_header_crc = archive_le32dec(p + 28);

	if (next_header_size == 0)
		/* There is no entry in an archive file. */
		return (ARCHIVE_EOF);

	if (((int64_t)next_header_offset) < 0) {
		archive_set_error(&a->archive, -1, "Malformed 7-Zip archive");
		return (ARCHIVE_FATAL);
	}
	if (__archive_read_seek(a, next_header_offset + zip->seek_base,
	    SEEK_SET) < 0)
		return (ARCHIVE_FATAL);
	zip->header_offset = next_header_offset;

	if ((p = __archive_read_ahead(a, next_header_size, NULL)) == NULL)
		return (ARCHIVE_FATAL);

	if (crc32(0, p, next_header_size) != next_header_crc) {
		archive_set_error(&a->archive, -1, "Damaged 7-Zip archive");
		return (ARCHIVE_FATAL);
	}

	len = next_header_size;
	/* Parse ArchiveProperties. */
	switch (p[0]) {
	case kEncodedHeader:
		p++;
		len--;

		/*
		 * The archive has an encoded header and we have to decode it
		 * in order to parse the header correctly.
		 */
		image_bytes =
		    decode_header_image(a, zip, &(zip->si), p, len, &image);
		free_StreamsInfo(&(zip->si));
		memset(&(zip->si), 0, sizeof(zip->si));
		if (image_bytes < 0)
			return (ARCHIVE_FATAL);
		p = image;
		len = image_bytes;
		/* FALL THROUGH */
	case kHeader:
		/*
		 * Parse the header.
		 */
		errno = 0;
		r = read_Header(zip, header, p, len);
		if (r < 0) {
			if (errno == ENOMEM)
				archive_set_error(&a->archive, -1,
				    "Couldn't allocate memory");
			else
				archive_set_error(&a->archive, -1,
				    "Damaged 7-Zip archive");
			return (ARCHIVE_FATAL);
		}
		if (len - r == 0 || p[r] != kEnd) {
			archive_set_error(&a->archive, -1,
			    "Malformed 7-Zip archive");
			return (ARCHIVE_FATAL);
		}
		break;
	default:
		archive_set_error(&a->archive, -1,
		    "Unexpected Property ID = %X", p[0]);
		return (ARCHIVE_FATAL);
	}
	zip->stream_offset = -1;

	/*
	 * If the uncompressed buffer was allocated more than 64K for
	 * the header image, release it.
	 */
	if (zip->uncompressed_buffer != NULL &&
	    zip->uncompressed_buffer_size != 64 * 1024) {
		free(zip->uncompressed_buffer);
		zip->uncompressed_buffer = NULL;
		zip->uncompressed_buffer_size = 0;
	}

	return (ARCHIVE_OK);
}