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

