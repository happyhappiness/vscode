(size_t b = 0; b < 256; ++b)
			crc32_table[s][b] = bswap32(crc32_table[s][b])