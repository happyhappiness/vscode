{
			const uint32_t cur_and_len_price = price
					+ get_len_price(&coder->rep_len_encoder,
							len_test, pos_state);

			if (cur_and_len_price < coder->opts[cur + len_test].price) {
				coder->opts[cur + len_test].price = cur_and_len_price;
				coder->opts[cur + len_test].pos_prev = cur;
				coder->opts[cur + len_test].back_prev = rep_index;
				coder->opts[cur + len_test].prev_1_is_literal = false;
			}
		}