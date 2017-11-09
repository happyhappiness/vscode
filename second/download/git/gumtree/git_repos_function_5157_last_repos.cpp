static void checkout_all(const char *prefix, int prefix_length)
{
	int i, errs = 0;
	struct cache_entry *last_ce = NULL;

	for (i = 0; i < active_nr ; i++) {
		struct cache_entry *ce = active_cache[i];
		if (ce_stage(ce) != checkout_stage
		    && (CHECKOUT_ALL != checkout_stage || !ce_stage(ce)))
			continue;
		if (prefix && *prefix &&
		    (ce_namelen(ce) <= prefix_length ||
		     memcmp(prefix, ce->name, prefix_length)))
			continue;
		if (last_ce && to_tempfile) {
			if (ce_namelen(last_ce) != ce_namelen(ce)
			    || memcmp(last_ce->name, ce->name, ce_namelen(ce)))
				write_tempfile_record(last_ce->name, prefix);
		}
		if (checkout_entry(ce, &state,
		    to_tempfile ? topath[ce_stage(ce)] : NULL) < 0)
			errs++;
		last_ce = ce;
	}
	if (last_ce && to_tempfile)
		write_tempfile_record(last_ce->name, prefix);
	if (errs)
		/* we have already done our error reporting.
		 * exit with the same code as die().
		 */
		exit(128);
}