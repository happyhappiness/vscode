{
			// Careful here: base - pos_slot - 1 can be -1, but
			// rc_bittree_reverse starts at probs[1], not probs[0].
			rc_bittree_reverse(&coder->rc,
				coder->pos_special + base - pos_slot - 1,
				footer_bits, pos_reduced);
		}