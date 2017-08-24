(len_best == mf->nice_len) {
			uint8_t *p1;
			uint8_t *p2;

			// The limit for the match length is either the
			// maximum match length supported by the LZ-based
			// encoder or the number of bytes left in the
			// dictionary, whichever is smaller.
			uint32_t limit = mf_avail(mf) + 1;
			if (limit > mf->match_len_max)
				limit = mf->match_len_max;

			// Pointer to the byte we just ran through
			// the match finder.
			p1 = mf_ptr(mf) - 1;

			// Pointer to the beginning of the match. We need -1
			// here because the match distances are zero based.
			p2 = p1 - matches[count - 1].dist - 1;

			while (len_best < limit
					&& p1[len_best] == p2[len_best])
				++len_best;
		}