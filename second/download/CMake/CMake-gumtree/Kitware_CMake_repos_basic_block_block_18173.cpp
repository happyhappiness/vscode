{
		const uint8_t *cur;
		uint32_t pos;
		uint32_t hash_value; /* hash_2_calc */
		uint32_t cur_match;

		header_skip(true, 2);

		hash_2_calc();

		cur_match = mf->hash[hash_value];
		mf->hash[hash_value] = pos;

		bt_skip();

	}