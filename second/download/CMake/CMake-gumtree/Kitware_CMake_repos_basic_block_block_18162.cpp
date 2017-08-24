{
		const uint8_t *cur;
		uint32_t pos;
		uint32_t temp, hash_value, hash_2_value; /* hash_3_calc */
		uint32_t cur_match;

		if (mf_avail(mf) < 3) {
			move_pending(mf);
			continue;
		}

		cur = mf_ptr(mf);
		pos = mf->read_pos + mf->offset;

		hash_3_calc();

		cur_match = mf->hash[FIX_3_HASH_SIZE + hash_value];

		mf->hash[hash_2_value] = pos;
		mf->hash[FIX_3_HASH_SIZE + hash_value] = pos;

		hc_skip();

	}