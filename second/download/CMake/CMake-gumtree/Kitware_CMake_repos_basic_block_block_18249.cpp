{
		const uint32_t pos_slot = get_pos_slot(i);
		const uint32_t footer_bits = ((pos_slot >> 1) - 1);
		const uint32_t base = (2 | (pos_slot & 1)) << footer_bits;
		const uint32_t price = rc_bittree_reverse_price(
				coder->pos_special + base - pos_slot - 1,
				footer_bits, i - base);

		for (len_to_pos_state = 0;
				len_to_pos_state < LEN_TO_POS_STATES;
				++len_to_pos_state)
			coder->distances_prices[len_to_pos_state][i]
					= price + coder->pos_slot_prices[
						len_to_pos_state][pos_slot];
	}