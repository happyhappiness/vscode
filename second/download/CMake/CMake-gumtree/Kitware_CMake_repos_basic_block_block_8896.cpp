(match->matches > 0 &&
		    (r = match_path_inclusion(a, match, mbs, pathname)) != 0) {
			if (r < 0)
				return (r);
			match->matches++;
			return (0);
		}