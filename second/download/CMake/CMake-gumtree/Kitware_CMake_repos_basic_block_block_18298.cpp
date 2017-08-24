(coder->opts[cur].prev_2) {
			state = coder->opts[coder->opts[cur].pos_prev_2].state;

			if (coder->opts[cur].back_prev_2 < REP_DISTANCES)
				update_long_rep(state);
			else
				update_match(state);

		} else {
			state = coder->opts[pos_prev].state;
		}