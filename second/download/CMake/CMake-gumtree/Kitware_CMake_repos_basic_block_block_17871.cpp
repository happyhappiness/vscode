{
		uint64_t r = b;
		for (size_t i = 0; i < 8; ++i) {
			if (r & 1)
				r = (r >> 1) ^ poly64;
			else
				r >>= 1;
		}

		crc64_table[b] = r;
	}