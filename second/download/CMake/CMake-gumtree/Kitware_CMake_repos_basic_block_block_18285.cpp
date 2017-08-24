{

		const uint32_t short_rep_price = rep_match_price
				+ get_short_rep_price(coder, state, pos_state);

		if (short_rep_price <= coder->opts[cur + 1].price) {
			coder->opts[cur + 1].price = short_rep_price;
			coder->opts[cur + 1].pos_prev = cur;
			make_short_rep(&coder->opts[cur + 1]);
			next_is_literal = true;
		}
	}