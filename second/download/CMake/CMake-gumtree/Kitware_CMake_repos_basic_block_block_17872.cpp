{
		crc = crc64_table[*buf++ ^ (crc & 0xFF)] ^ (crc >> 8);
		--size;
	}