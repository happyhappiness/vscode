	unsigned int match_cnt = 0, annotated_cnt = 0, cur_match;
	unsigned long seen_commits = 0;
	unsigned int unannotated_cnt = 0;

	if (get_oid(arg, &oid))
		die(_("Not a valid object name %s"), arg);
	cmit = lookup_commit_reference(&oid);
	if (!cmit)
		die(_("%s is not a valid '%s' object"), arg, commit_type);

	n = find_commit_name(&cmit->object.oid);
	if (n && (tags || all || n->prio == 2)) {
		/*
