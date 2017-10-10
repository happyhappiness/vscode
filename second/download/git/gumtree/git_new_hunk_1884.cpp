	cb.cutoff_tz = cutoff_tz;
	cb.cutoff_cnt = cutoff_cnt;
	cb.sha1 = sha1;

	for_each_reflog_ent_reverse(refname, read_ref_at_ent, &cb);

	if (!cb.reccnt) {
		if (flags & GET_SHA1_QUIETLY)
			exit(128);
		else
			die("Log for %s is empty.", refname);
	}
	if (cb.found_it)
		return 0;

	for_each_reflog_ent(refname, read_ref_at_ent_oldest, &cb);

	return 1;
