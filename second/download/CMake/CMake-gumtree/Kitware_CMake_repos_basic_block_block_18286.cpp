{
		coder->opts[cur + 1].price = cur_and_1_price;
		coder->opts[cur + 1].pos_prev = cur;
		make_literal(&coder->opts[cur + 1]);
		next_is_literal = true;
	}