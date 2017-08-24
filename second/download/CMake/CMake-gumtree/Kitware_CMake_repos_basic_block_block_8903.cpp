{
	struct match *match;
	struct match *matched;
	int r;

	if (a == NULL)
		return (0);

	/* Mark off any unmatched inclusions. */
	/* In particular, if a filename does appear in the archive and
	 * is explicitly included and excluded, then we don't report
	 * it as missing even though we don't extract it.
	 */
	matched = NULL;
	for (match = a->inclusions.first; match != NULL;
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

	/* Exclusions take priority */
	for (match = a->exclusions.first; match != NULL;
	    match = match->next){
		r = match_path_exclusion(a, match, mbs, pathname);
		if (r)
			return (r);
	}

	/* It's not excluded and we found an inclusion above, so it's
	 * included. */
	if (matched != NULL)
		return (0);


	/* We didn't find an unmatched inclusion, check the remaining ones. */
	for (match = a->inclusions.first; match != NULL;
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

	/* If there were inclusions, default is to exclude. */
	if (a->inclusions.first != NULL)
	    return (1);

	/* No explicit inclusions, default is to match. */
	return (0);
}