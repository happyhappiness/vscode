{
		crc = lzma_crc32_table[0][*buf++ ^ (crc & 0xFF)] ^ (crc >> 8);
		--size;
	}