(match = a->exclusions.first; match != NULL;
	    match = match->next){
		r = match_path_exclusion(a, match, mbs, pathname);
		if (r)
			return (r);
	}