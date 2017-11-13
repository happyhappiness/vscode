int verify_bundle(struct bundle_header *header, int verbose)
{
	/*
	 * Do fast check, then if any prereqs are missing then go line by line
	 * to be verbose about the errors
	 */
	struct ref_list *p = &header->prerequisites;
	struct rev_info revs;
	const char *argv[] = {NULL, "--all", NULL};
	struct object_array refs;
	struct commit *commit;
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

	refs = revs.pending;
	revs.leak_pending = 1;

	if (prepare_revision_walk(&revs))
		die(_("revision walk setup failed"));

	i = req_nr;
	while (i && (commit = get_revision(&revs)))
		if (commit->object.flags & PREREQ_MARK)
			i--;

	for (i = 0; i < req_nr; i++)
		if (!(refs.objects[i].item->flags & SHOWN)) {
			if (++ret == 1)
				error("%s", message);
			error("%s %s", sha1_to_hex(refs.objects[i].item->sha1),
				refs.objects[i].name);
		}

	clear_commit_marks_for_object_array(&refs, ALL_REV_FLAGS);
	free(refs.objects);

	if (verbose) {
		struct ref_list *r;

		r = &header->references;
		printf_ln(Q_("The bundle contains this ref:",
			     "The bundle contains these %d refs:",
			     r->nr),
			  r->nr);
		list_refs(r, 0, NULL);
		r = &header->prerequisites;
		if (!r->nr) {
			printf_ln(_("The bundle records a complete history."));
		} else {
			printf_ln(Q_("The bundle requires this ref:",
				     "The bundle requires these %d refs:",
				     r->nr),
				  r->nr);
			list_refs(r, 0, NULL);
		}
	}
	return ret;
}