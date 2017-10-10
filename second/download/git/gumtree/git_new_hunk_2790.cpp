	struct object_array refs;

	init_revisions(&revs, NULL);
	setup_revisions(0, NULL, &revs, NULL);

	object->flags &= ~UNINTERESTING;
	add_pending_object(&revs, object, oid_to_hex(&object->oid));

	for_each_ref(add_pending_uninteresting_ref, &revs);
	add_pending_sha1(&revs, "HEAD", new->object.oid.hash, UNINTERESTING);

	refs = revs.pending;
	revs.leak_pending = 1;

	if (prepare_revision_walk(&revs))
		die(_("internal error in revision walk"));
