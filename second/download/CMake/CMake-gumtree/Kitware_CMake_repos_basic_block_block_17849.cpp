(size_t i = 0; i < 8; ++i) {
			if (r & 1)
				r = (r >> 1) ^ poly32;
			else
				r >>= 1;
		}