static int checkout_file(const char *name, const char *prefix)
{
	int namelen = strlen(name);
	int pos = cache_name_pos(name, namelen);
	int has_same_name = 0;
	int did_checkout = 0;
	int errs = 0;

	if (pos < 0)
		pos = -pos - 1;

	while (pos < active_nr) {
		struct cache_entry *ce = active_cache[pos];
		if (ce_namelen(ce) != namelen ||
		    memcmp(ce->name, name, namelen))
			break;
		has_same_name = 1;
		pos++;
		if (ce_stage(ce) != checkout_stage
		    && (CHECKOUT_ALL != checkout_stage || !ce_stage(ce)))
			continue;
		did_checkout = 1;
		if (checkout_entry(ce, &state,
		    to_tempfile ? topath[ce_stage(ce)] : NULL) < 0)
			errs++;
	}

	if (did_checkout) {
		if (to_tempfile)
			write_tempfile_record(name, prefix);
		return errs > 0 ? -1 : 0;
	}

	if (!state.quiet) {
		fprintf(stderr, "git checkout-index: %s ", name);
		if (!has_same_name)
			fprintf(stderr, "is not in the cache");
		else if (checkout_stage)
			fprintf(stderr, "does not exist at stage %d",
				checkout_stage);
		else
			fprintf(stderr, "is unmerged");
		fputc('\n', stderr);
	}
	return -1;
}