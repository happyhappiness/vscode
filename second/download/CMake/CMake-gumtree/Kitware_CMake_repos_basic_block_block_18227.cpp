{
			// It's a repeated match i.e. the same distance
			// has been used earlier.
			rc_bit(&coder->rc, &coder->is_rep[coder->state], 1);
			rep_match(coder, pos_state, back, len);
		}