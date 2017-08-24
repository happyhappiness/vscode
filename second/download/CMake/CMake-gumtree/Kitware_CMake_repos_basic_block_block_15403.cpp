{
			/*
			 * Encode the header in order to reduce the size
			 * of the archive.
			 */
			free(zip->coder.props);
			zip->coder.codec = header_compression;
			zip->coder.prop_size = zip->stream.prop_size;
			zip->coder.props = zip->stream.props;
			zip->stream.prop_size = 0;
			zip->stream.props = NULL;

			r = _7z_compression_init_encoder(a, _7Z_COPY, 0);
			if (r < 0)
				return (r);
			zip->crc32flg = ENCODED_CRC32;
			zip->encoded_crc32 = 0;

			/*
			 * Make EncodedHeader.
			 */
			r = enc_uint64(a, kEncodedHeader);
			if (r < 0)
				return (r);
			r = make_streamsInfo(a, header_offset, header_size,
			      header_unpacksize, 1, &(zip->coder), 0,
			      header_crc32);
			if (r < 0)
				return (r);
			r = (int)compress_out(a, NULL, 0, ARCHIVE_Z_FINISH);
			if (r < 0)
				return (r);
			header_offset = header_offset + header_size;
			header_size = zip->stream.total_out;
			header_crc32 = zip->encoded_crc32;
		}