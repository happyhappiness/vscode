(match = a->inclusions.first; match != NULL;
	    match = match->next){
		if (match->matches == 0 &&
		    (r = match_path_inclusion(a, match, mbs, pathname)) != 0) {
			if (r < 0)
				return (r);
			a->inclusions.unmatched_count--;
			match->matches++;
			matched = match;
		}
	}