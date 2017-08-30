		archive_set_error(&a->archive, -1, "Malformed 7-Zip archive");
		return (ARCHIVE_FATAL);
	}
	__archive_read_consume(a, 32);
	if (next_header_offset != 0) {
		if (bytes_avail >= next_header_offset)
			__archive_read_consume(a, next_header_offset);
		else if (__archive_read_seek(a,
		    next_header_offset + zip->seek_base, SEEK_SET) < 0)
			return (ARCHIVE_FATAL);
	}
	zip->stream_offset = next_header_offset;
	zip->header_offset = next_header_offset;
	zip->header_bytes_remaining = next_header_size;
	zip->header_crc32 = 0;
	zip->header_is_encoded = 0;
	zip->header_is_being_read = 1;
	check_header_crc = 1;

	if ((p = header_bytes(a, 1)) == NULL) {
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT,
		    "Truncated 7-Zip file body");
		return (ARCHIVE_FATAL);
	}
	/* Parse ArchiveProperties. */
	switch (p[0]) {
	case kEncodedHeader:
		/*
		 * The archive has an encoded header and we have to decode it
		 * in order to parse the header correctly.
		 */
		r = decode_encoded_header_info(a, &(zip->si));

		/* Check the EncodedHeader CRC.*/
		if (r == 0 && zip->header_crc32 != next_header_crc) {
			archive_set_error(&a->archive, -1,
			    "Damaged 7-Zip archive");
			r = -1;
		}
		if (r == 0) {
			if (zip->si.ci.folders[0].digest_defined)
				next_header_crc = zip->si.ci.folders[0].digest;
			else
				check_header_crc = 0;
			if (zip->pack_stream_bytes_unconsumed)
				read_consume(a);
			r = setup_decode_folder(a, zip->si.ci.folders, 1);
			if (r == 0) {
				zip->header_bytes_remaining =
					zip->folder_outbytes_remaining;
				r = seek_pack(a);
			}
		}
		/* Clean up StreamsInfo. */
		free_StreamsInfo(&(zip->si));
		memset(&(zip->si), 0, sizeof(zip->si));
		if (r < 0)
			return (ARCHIVE_FATAL);
		zip->header_is_encoded = 1;
		zip->header_crc32 = 0;
		/* FALL THROUGH */
	case kHeader:
		/*
		 * Parse the header.
		 */
		errno = 0;
		r = read_Header(a, header, zip->header_is_encoded);
		if (r < 0) {
			if (errno == ENOMEM)
				archive_set_error(&a->archive, -1,
