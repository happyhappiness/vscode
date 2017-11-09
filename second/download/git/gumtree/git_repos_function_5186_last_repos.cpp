static void orphaned_commit_warning(struct commit *old, struct commit *new)
{
	struct rev_info revs;
	struct object *object = &old->object;
	struct object_array refs;

	init_revisions(&revs, NULL);
	setup_revisions(0, NULL, &revs, NULL);

	object->flags &= ~UNINTERESTING;
	add_pending_object(&revs, object, oid_to_hex(&object->oid));

	for_each_ref(add_pending_uninteresting_ref, &revs);
	add_pending_oid(&revs, "HEAD", &new->object.oid, UNINTERESTING);

	refs = revs.pending;
	revs.leak_pending = 1;

	if (prepare_revision_walk(&revs))
		die(_("internal error in revision walk"));
	if (!(old->object.flags & UNINTERESTING))
		suggest_reattach(old, &revs);
	else
		describe_detached_head(_("Previous HEAD position was"), old);

	clear_commit_marks_for_object_array(&refs, ALL_REV_FLAGS);
	free(refs.objects);
}