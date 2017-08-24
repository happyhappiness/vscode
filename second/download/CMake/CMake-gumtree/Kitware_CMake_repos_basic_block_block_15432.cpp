{
		uint8_t crc[4];
		/*
		 * Make CRC.
		 */
		r = enc_uint64(a, kCRC);
		if (r < 0)
			return (r);

		/* All are defined */
		r = enc_uint64(a, 1);
		if (r < 0)
			return (r);
		archive_le32enc(crc, header_crc);
		r = (int)compress_out(a, crc, 4, ARCHIVE_Z_RUN);
		if (r < 0)
			return (r);
	}