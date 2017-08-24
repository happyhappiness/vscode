{
		unsigned int j;
		uint16_t crc = (uint16_t)i;
		for (j = 8; j; j--)
			crc = (crc >> 1) ^ ((crc & 1) * 0xA001);
		crc16tbl[0][i] = crc;
	}