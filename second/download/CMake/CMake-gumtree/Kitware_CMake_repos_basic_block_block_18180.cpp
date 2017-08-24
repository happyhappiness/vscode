{
	const uint8_t *cur;
	uint32_t pos;
	uint32_t temp, hash_value, hash_2_value, hash_3_value; /* hash_4_calc */
	uint32_t delta2, delta3, cur_match;
	uint32_t len_best = 1;
	uint32_t matches_count = 0;

	header_find(true, 4);

	hash_4_calc();

	delta2 = pos - mf->hash[hash_2_value];
	delta3 = pos - mf->hash[FIX_3_HASH_SIZE + hash_3_value];
	cur_match = mf->hash[FIX_4_HASH_SIZE + hash_value];

	mf->hash[hash_2_value] = pos;
	mf->hash[FIX_3_HASH_SIZE + hash_3_value] = pos;
	mf->hash[FIX_4_HASH_SIZE + hash_value] = pos;

	if (delta2 < mf->cyclic_size && *(cur - delta2) == *cur) {
		len_best = 2;
		matches[0].len = 2;
		matches[0].dist = delta2 - 1;
		matches_count = 1;
	}

	if (delta2 != delta3 && delta3 < mf->cyclic_size
			&& *(cur - delta3) == *cur) {
		len_best = 3;
		matches[matches_count++].dist = delta3 - 1;
		delta2 = delta3;
	}

	if (matches_count != 0) {
		for ( ; len_best != len_limit; ++len_best)
			if (*(cur + len_best - delta2) != cur[len_best])
				break;

		matches[matches_count - 1].len = len_best;

		if (len_best == len_limit) {
			bt_skip();
			return matches_count;
		}
	}

	if (len_best < 3)
		len_best = 3;

	bt_find(len_best);
}