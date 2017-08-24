		if ((r = seek_pack(a)) < 0)
			return (r);
		zip->pack_stream_bytes_unconsumed =
		    (size_t)zip->pack_stream_inbytes_remaining;
		read_consume(a);

		/* Read following three sub streams. */
		for (i = 0; i < 3; i++) {
			const struct _7z_coder *coder = scoder[i];

			if ((r = seek_pack(a)) < 0) {
				free(b[0]); free(b[1]); free(b[2]);
				return (r);
			}

			if (sunpack[i] == (uint64_t)-1)
				zip->folder_outbytes_remaining =
				    zip->pack_stream_inbytes_remaining;
			else
				zip->folder_outbytes_remaining = sunpack[i];

			r = init_decompression(a, zip, coder, NULL);
			if (r != ARCHIVE_OK) {
				free(b[0]); free(b[1]); free(b[2]);
				return (ARCHIVE_FATAL);
			}

			/* Allocate memory for the decorded data of a sub
			 * stream. */
			b[i] = malloc((size_t)zip->folder_outbytes_remaining);
			if (b[i] == NULL) {
				free(b[0]); free(b[1]); free(b[2]);
				archive_set_error(&a->archive, ENOMEM,
				    "No memory for 7-Zip decompression");
				return (ARCHIVE_FATAL);
			}

			/* Extract a sub stream. */
			while (zip->pack_stream_inbytes_remaining > 0) {
				r = (int)extract_pack_stream(a, 0);
				if (r < 0) {
					free(b[0]); free(b[1]); free(b[2]);
					return (r);
				}
				bytes = get_uncompressed_data(a, &buff,
				    zip->uncompressed_buffer_bytes_remaining,
				    0);
				if (bytes < 0) {
					free(b[0]); free(b[1]); free(b[2]);
					return ((int)bytes);
				}
				memcpy(b[i]+s[i], buff, bytes);
				s[i] += bytes;
				if (zip->pack_stream_bytes_unconsumed)
