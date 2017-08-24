{
		uint32_t match_bit;
		uint32_t subcoder_index;
		uint32_t bit;

		match_byte <<= 1;
		match_bit = match_byte & offset;
		subcoder_index = offset + match_bit + (symbol >> 8);
		bit = (symbol >> 7) & 1;
		rc_bit(rc, &subcoder[subcoder_index], bit);

		symbol <<= 1;
		offset &= ~(match_byte ^ symbol);

	}