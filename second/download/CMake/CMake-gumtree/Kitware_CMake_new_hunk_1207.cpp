		zip->stream.opaque = Z_NULL;

		zip->stream.next_out = zip->buf;

		zip->stream.avail_out = zip->len_buf;

		if (deflateInit2(&zip->stream, Z_DEFAULT_COMPRESSION,

		    Z_DEFLATED, -15, 8, Z_DEFAULT_STRATEGY) != Z_OK) {

			archive_set_error(&a->archive, ENOMEM,

			    "Can't init deflate compressor");

			return (ARCHIVE_FATAL);

