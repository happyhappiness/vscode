{
			assert(matches[i].len <= mf->nice_len);
			assert(matches[i].dist < mf->read_pos);
			assert(memcmp(mf_ptr(mf) - 1,
				mf_ptr(mf) - matches[i].dist - 2,
				matches[i].len) == 0);
		}