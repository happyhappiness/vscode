{
		const uint32_t bit = symbol & 1;
		symbol >>= 1;
		rc_bit(rc, &probs[model_index], bit);
		model_index = (model_index << 1) + bit;
	}