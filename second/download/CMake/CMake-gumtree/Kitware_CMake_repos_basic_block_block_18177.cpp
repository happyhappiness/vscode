{
		for ( ; len_best != len_limit; ++len_best)
			if (*(cur + len_best - delta2) != cur[len_best])
				break;

		matches[0].len = len_best;
		matches[0].dist = delta2 - 1;
		matches_count = 1;

		if (len_best == len_limit) {
			bt_skip();
			return 1; // matches_count
		}
	}