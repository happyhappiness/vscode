{
		for (j = 0; j <= coder->pos_mask; ++j) {
			bit_reset(coder->is_match[i][j]);
			bit_reset(coder->is_rep0_long[i][j]);
		}

		bit_reset(coder->is_rep[i]);
		bit_reset(coder->is_rep0[i]);
		bit_reset(coder->is_rep1[i]);
		bit_reset(coder->is_rep2[i]);
	}