(; i < table_size && i < LEN_LOW_SYMBOLS + LEN_MID_SYMBOLS; ++i)
		prices[i] = b0 + rc_bittree_price(lc->mid[pos_state],
				LEN_MID_BITS, i - LEN_LOW_SYMBOLS)