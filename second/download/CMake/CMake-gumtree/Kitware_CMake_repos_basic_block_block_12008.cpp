{
		crc = (crc >> 8) ^ crc16tbl[0][(crc ^ *p++) & 0xff];
		len--;
	}