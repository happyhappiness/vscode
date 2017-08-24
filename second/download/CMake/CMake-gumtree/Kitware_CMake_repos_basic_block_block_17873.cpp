(size_t b = 0; b < 256; ++b)
			crc64_table[s][b] = bswap64(crc64_table[s][b])