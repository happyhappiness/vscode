(size_t s = 0; s < 4; ++s) {
		for (size_t b = 0; b < 256; ++b) {
			uint64_t r = s == 0 ? b : crc64_table[s - 1][b];

			for (size_t i = 0; i < 8; ++i) {
				if (r & 1)
					r = (r >> 1) ^ poly64;
				else
					r >>= 1;
			}

			crc64_table[s][b] = r;
		}
	}