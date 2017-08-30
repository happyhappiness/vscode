		return (ARCHIVE_FATAL);

	}



	return (ARCHIVE_OK);

}



static const unsigned char *

header_bytes(struct archive_read *a, size_t rbytes)

{

	struct _7zip *zip = (struct _7zip *)a->format->data;

	const unsigned char *p;



	if (zip->header_bytes_remaining < rbytes)

		return (NULL);

	if (zip->pack_stream_bytes_unconsumed)

		read_consume(a);



	if (zip->header_is_encoded == 0) {

		p = __archive_read_ahead(a, rbytes, NULL);

		if (p == NULL)

			return (NULL);

		zip->header_bytes_remaining -= rbytes;

		zip->pack_stream_bytes_unconsumed = rbytes;

	} else {

		const void *buff;

		ssize_t bytes;



		bytes = read_stream(a, &buff, rbytes, rbytes);

		if (bytes <= 0)

			return (NULL);

		zip->header_bytes_remaining -= bytes;

		p = buff;

	}



	/* Update checksum */

	zip->header_crc32 = crc32(zip->header_crc32, p, rbytes);

	return (p);

}



static int

slurp_central_directory(struct archive_read *a, struct _7zip *zip,

    struct _7z_header_info *header)

{

	const unsigned char *p;

	uint64_t next_header_offset;

	uint64_t next_header_size;

	uint32_t next_header_crc;

	ssize_t bytes_avail;

	int check_header_crc, r;



	if ((p = __archive_read_ahead(a, 32, &bytes_avail)) == NULL)

		return (ARCHIVE_FATAL);

