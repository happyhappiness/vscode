{
		const uint32_t bit = (symbol >> --bit_count) & 1;
		rc_bit(rc, &probs[model_index], bit);
		model_index = (model_index << 1) + bit;
	}