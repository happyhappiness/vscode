(uint8_t slot_fast = 2; slot_fast < fast_slots; ++slot_fast) {
		const uint32_t k = 1 << ((slot_fast >> 1) - 1);
		for (uint32_t j = 0; j < k; ++j, ++c)
			fastpos[c] = slot_fast;
	}