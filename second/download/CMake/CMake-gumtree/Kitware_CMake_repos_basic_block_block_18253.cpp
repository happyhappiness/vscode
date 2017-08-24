(pos_slot = END_POS_MODEL_INDEX;
				pos_slot < coder->dist_table_size; ++pos_slot)
			pos_slot_prices[pos_slot] += rc_direct_price(
					((pos_slot >> 1) - 1) - ALIGN_BITS)