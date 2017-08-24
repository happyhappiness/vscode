{
		const uint8_t *cur;
		uint32_t pos;
		uint32_t temp, hash_value, hash_2_value; /* hash_3_calc */
		uint32_t cur_match;

		header_skip(true, 3);

		hash_3_calc();

		cur_match = mf->hash[FIX_3_HASH_SIZE + hash_value];

		mf->hash[hash_2_value] = pos;
		mf->hash[FIX_3_HASH_SIZE + hash_value] = pos;

		bt_skip();

	}