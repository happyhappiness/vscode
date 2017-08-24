{
						coder->opts[offset].price = cur_and_len_price;
						coder->opts[offset].pos_prev = cur + len_test + 1;
						coder->opts[offset].back_prev = 0;
						coder->opts[offset].prev_1_is_literal = true;
						coder->opts[offset].prev_2 = true;
						coder->opts[offset].pos_prev_2 = cur;
						coder->opts[offset].back_prev_2
								= cur_back + REP_DISTANCES;
					}