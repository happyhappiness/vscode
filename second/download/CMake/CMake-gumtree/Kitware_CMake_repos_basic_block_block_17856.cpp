(size_t b = 0; b < 256; ++b) {
			uint32_t r = s == 0 ? b : crc32_table[s - 1][b];

			for (size_t i = 0; i < 8; ++i) {
				if (r & 1)
					r = (r >> 1) ^ poly32;
				else
					r >>= 1;
			}

			crc32_table[s][b] = r;
		}