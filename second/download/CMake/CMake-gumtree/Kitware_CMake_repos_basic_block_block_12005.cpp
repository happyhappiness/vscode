(j = 8; j; j--)
			crc = (crc >> 1) ^ ((crc & 1) * 0xA001)