(i = 0; i < 256; i++) {
		crc16tbl[1][i] = (crc16tbl[0][i] >> 8)
			^ crc16tbl[0][crc16tbl[0][i] & 0xff];
	}