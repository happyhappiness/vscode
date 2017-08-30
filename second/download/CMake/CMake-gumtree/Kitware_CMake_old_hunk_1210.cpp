		return (ARCHIVE_FATAL);

	}



	r = setup_decode_folder(a, si->ci.folders, 1);

	if (r != ARCHIVE_OK)

		return (ARCHIVE_FATAL);



	/* Get an uncompressed header size. */

	vsize = (size_t)zip->folder_outbytes_remaining;



	/*

	 * Allocate an uncompressed buffer for the header image.

	 */

	zip->uncompressed_buffer_size = 64 * 1024;

	if (vsize > zip->uncompressed_buffer_size)

		zip->uncompressed_buffer_size = vsize;

	zip->uncompressed_buffer = malloc(zip->uncompressed_buffer_size);

	if (zip->uncompressed_buffer == NULL) {

		archive_set_error(&a->archive, ENOMEM,

		    "No memory for 7-Zip decompression");

		return (ARCHIVE_FATAL);

	}



	/* Get the bytes we can read to decode the header. */

	zip->pack_stream_inbytes_remaining = si->pi.sizes[0];



	/* Seek the read point. */

	if (__archive_read_seek(a, si->pi.pos + zip->seek_base, SEEK_SET) < 0)

		return (ARCHIVE_FATAL);

	zip->header_offset = si->pi.pos;



	/* Extract a pack stream. */

	r = extract_pack_stream(a);

	if (r < 0)

		return (r);

	for (;;) {

		ssize_t bytes;

		

		bytes = get_uncompressed_data(a, image, vsize);

		if (bytes < 0)

			return (r);

		if (bytes != vsize) {

			if (*image != zip->uncompressed_buffer) {

				/* This might happen if the coder was COPY.

				 * We have to make sure we read a full plain

				 * header image. */

				if (NULL==__archive_read_ahead(a, vsize, NULL))

					return (ARCHIVE_FATAL);

				continue;

			} else {

				archive_set_error(&a->archive, -1,

				    "Malformed 7-Zip archive file");

				return (ARCHIVE_FATAL);

			}

		}

		break;

	}

	v = *image;



	/* Clean up variables which will not be used for decoding the

	 * archive header */

	zip->pack_stream_remaining = 0;

	zip->pack_stream_index = 0;

	zip->folder_outbytes_remaining = 0;

	zip->uncompressed_buffer_bytes_remaining = 0;

	zip->pack_stream_bytes_unconsumed = 0;



	/* Check the header CRC. */

	if (si->ci.folders[0].digest_defined){

		uint32_t c = crc32(0, v, vsize);

		if (c != si->ci.folders[0].digest) {

			archive_set_error(&a->archive, -1, "Header CRC error");

			return (ARCHIVE_FATAL);

		}

	}

	return ((ssize_t)vsize);

}



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

