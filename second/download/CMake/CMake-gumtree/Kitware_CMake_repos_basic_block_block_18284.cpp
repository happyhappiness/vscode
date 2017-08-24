{
			coder->opts[cur + 1].price = short_rep_price;
			coder->opts[cur + 1].pos_prev = cur;
			make_short_rep(&coder->opts[cur + 1]);
			next_is_literal = true;
		}