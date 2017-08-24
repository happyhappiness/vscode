(;file != NULL; file = file->next) {
		uint8_t crc[4];
		if (file->size == 0)
			break;
		archive_le32enc(crc, file->crc32);
		r = (int)compress_out(a, crc, 4, ARCHIVE_Z_RUN);
		if (r < 0)
			return (r);
	}