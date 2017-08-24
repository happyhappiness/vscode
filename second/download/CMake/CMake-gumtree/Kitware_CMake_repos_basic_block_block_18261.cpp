{
				coder->opts[cur + len_test].price = cur_and_len_price;
				coder->opts[cur + len_test].pos_prev = cur;
				coder->opts[cur + len_test].back_prev
						= cur_back + REP_DISTANCES;
				coder->opts[cur + len_test].prev_1_is_literal = false;
			}