(match = a->inclusions.first; match != NULL;
	    match = match->next){
		/* We looked at previously-unmatched inclusions already. */
		if (match->matches > 0 &&
		    (r = match_path_inclusion(a, match, mbs, pathname)) != 0) {
			if (r < 0)
				return (r);
			match->matches++;
			return (0);
		}
	}