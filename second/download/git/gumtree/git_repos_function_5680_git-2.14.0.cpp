static void get_patch_ids(struct rev_info *rev, struct patch_ids *ids)
{
	struct rev_info check_rev;
	struct commit *commit, *c1, *c2;
	struct object *o1, *o2;
	unsigned flags1, flags2;

	if (rev->pending.nr != 2)
		die(_("Need exactly one range."));

	o1 = rev->pending.objects[0].item;
	o2 = rev->pending.objects[1].item;
	flags1 = o1->flags;
	flags2 = o2->flags;
	c1 = lookup_commit_reference(&o1->oid);
	c2 = lookup_commit_reference(&o2->oid);

	if ((flags1 & UNINTERESTING) == (flags2 & UNINTERESTING))
		die(_("Not a range."));

	init_patch_ids(ids);

	/* given a range a..b get all patch ids for b..a */
	init_revisions(&check_rev, rev->prefix);
	check_rev.max_parents = 1;
	o1->flags ^= UNINTERESTING;
	o2->flags ^= UNINTERESTING;
	add_pending_object(&check_rev, o1, "o1");
	add_pending_object(&check_rev, o2, "o2");
	if (prepare_revision_walk(&check_rev))
		die(_("revision walk setup failed"));

	while ((commit = get_revision(&check_rev)) != NULL) {
		add_commit_patch_id(commit, ids);
	}

	/* reset for next revision walk */
	clear_commit_marks(c1, SEEN | UNINTERESTING | SHOWN | ADDED);
	clear_commit_marks(c2, SEEN | UNINTERESTING | SHOWN | ADDED);
	o1->flags = flags1;
	o2->flags = flags2;
}