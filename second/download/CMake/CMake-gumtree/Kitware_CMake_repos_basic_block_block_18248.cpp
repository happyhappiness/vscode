(len_to_pos_state = 0;
				len_to_pos_state < LEN_TO_POS_STATES;
				++len_to_pos_state)
			coder->distances_prices[len_to_pos_state][i]
					= price + coder->pos_slot_prices[
						len_to_pos_state][pos_slot]