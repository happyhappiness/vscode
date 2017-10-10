	int i, ret = 0, req_nr;
	const char *message = _("Repository lacks these prerequisite commits:");

	init_revisions(&revs, NULL);
	for (i = 0; i < p->nr; i++) {
		struct ref_list_entry *e = p->list + i;
		struct object *o = parse_object(e->sha1);
		if (o) {
			o->flags |= PREREQ_MARK;
			add_pending_object(&revs, o, e->name);
			continue;
		}
		if (++ret == 1)
			error("%s", message);
		error("%s %s", sha1_to_hex(e->sha1), e->name);
	}
	if (revs.pending.nr != p->nr)
		return ret;
	req_nr = revs.pending.nr;
	setup_revisions(2, argv, &revs, NULL);

