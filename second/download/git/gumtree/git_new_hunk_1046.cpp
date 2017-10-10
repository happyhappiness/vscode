	ref_cbdata.filter = filter;

	if (type & FILTER_REFS_INCLUDE_BROKEN)
		broken = 1;
	filter->kind = type & FILTER_REFS_KIND_MASK;

	init_contains_cache(&ref_cbdata.contains_cache);
	init_contains_cache(&ref_cbdata.no_contains_cache);

	/*  Simple per-ref filtering */
	if (!filter->kind)
		die("filter_refs: invalid type");
	else {
		/*
		 * For common cases where we need only branches or remotes or tags,
