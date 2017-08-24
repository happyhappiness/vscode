(pos_state = 0; pos_state < num_pos_states; ++pos_state) {
		bittree_reset(lencoder->low[pos_state], LEN_LOW_BITS);
		bittree_reset(lencoder->mid[pos_state], LEN_MID_BITS);
	}