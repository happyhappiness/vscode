{
		// Round dictionary size up to the next 2^n - 1 so it can
		// be used as a hash mask.
		hs = lz_options->dict_size - 1;
		hs |= hs >> 1;
		hs |= hs >> 2;
		hs |= hs >> 4;
		hs |= hs >> 8;
		hs >>= 1;
		hs |= 0xFFFF;

		if (hs > (UINT32_C(1) << 24)) {
			if (hash_bytes == 3)
				hs = (UINT32_C(1) << 24) - 1;
			else
				hs >>= 1;
		}
	}