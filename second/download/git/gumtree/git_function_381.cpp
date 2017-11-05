static int everything_local(struct fetch_pack_args *args,
			    struct ref **refs,
			    struct ref **sought, int nr_sought)
{
	struct ref *ref;
	int retval;
	unsigned long cutoff = 0;

	save_commit_buffer = 0;

	for (ref = *refs; ref; ref = ref->next) {
		struct object *o;

		if (!has_object_file(&ref->old_oid))
			continue;

		o = parse_object(ref->old_oid.hash);
		if (!o)
			continue;

		/* We already have it -- which may mean that we were
		 * in sync with the other side at some time after
		 * that (it is OK if we guess wrong here).
		 */
		if (o->type == OBJ_COMMIT) {
			struct commit *commit = (struct commit *)o;
			if (!cutoff || cutoff < commit->date)
				cutoff = commit->date;
		}
	}

	if (!args->depth) {
		for_each_ref(mark_complete_oid, NULL);
		for_each_alternate_ref(mark_alternate_complete, NULL);
		commit_list_sort_by_date(&complete);
		if (cutoff)
			mark_recent_complete_commits(args, cutoff);
	}

	/*
	 * Mark all complete remote refs as common refs.
	 * Don't mark them common yet; the server has to be told so first.
	 */
	for (ref = *refs; ref; ref = ref->next) {
		struct object *o = deref_tag(lookup_object(ref->old_oid.hash),
					     NULL, 0);

		if (!o || o->type != OBJ_COMMIT || !(o->flags & COMPLETE))
			continue;

		if (!(o->flags & SEEN)) {
			rev_list_push((struct commit *)o, COMMON_REF | SEEN);

			mark_common((struct commit *)o, 1, 1);
		}
	}

	filter_refs(args, refs, sought, nr_sought);

	for (retval = 1, ref = *refs; ref ; ref = ref->next) {
		const unsigned char *remote = ref->old_oid.hash;
		struct object *o;

		o = lookup_object(remote);
		if (!o || !(o->flags & COMPLETE)) {
			retval = 0;
			if (!args->verbose)
				continue;
			fprintf(stderr,
				"want %s (%s)\n", sha1_to_hex(remote),
				ref->name);
			continue;
		}
		if (!args->verbose)
			continue;
		fprintf(stderr,
			"already have %s (%s)\n", sha1_to_hex(remote),
			ref->name);
	}
	return retval;
}