{
		const uint32_t cycles_bits = RC_BIT_PRICE_SHIFT_BITS;
		uint32_t w = i;
		uint32_t bit_count = 0;

		for (uint32_t j = 0; j < cycles_bits; ++j) {
			w *= w;
			bit_count <<= 1;

			while (w >= (UINT32_C(1) << 16)) {
				w >>= 1;
				++bit_count;
			}
		}

		rc_prices[i >> RC_MOVE_REDUCING_BITS]
				= (RC_BIT_MODEL_TOTAL_BITS << cycles_bits)
				- 15 - bit_count;
	}