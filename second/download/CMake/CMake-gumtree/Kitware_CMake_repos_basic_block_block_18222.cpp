{
		const uint32_t footer_bits = (pos_slot >> 1) - 1;
		const uint32_t base = (2 | (pos_slot & 1)) << footer_bits;
		const uint32_t pos_reduced = distance - base;

		if (pos_slot < END_POS_MODEL_INDEX) {
			// Careful here: base - pos_slot - 1 can be -1, but
			// rc_bittree_reverse starts at probs[1], not probs[0].
			rc_bittree_reverse(&coder->rc,
				coder->pos_special + base - pos_slot - 1,
				footer_bits, pos_reduced);
		} else {
			rc_direct(&coder->rc, pos_reduced >> ALIGN_BITS,
					footer_bits - ALIGN_BITS);
			rc_bittree_reverse(
					&coder->rc, coder->pos_align,
					ALIGN_BITS, pos_reduced & ALIGN_MASK);
			++coder->align_price_count;
		}
	}