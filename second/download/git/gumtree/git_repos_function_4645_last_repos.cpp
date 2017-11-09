static int everything_local(struct fetch_pack_args *args,
			    struct ref **refs,
			    struct ref **sought, int nr_sought)
{
	struct ref *ref;
	int retval;
	timestamp_t cutoff = 0;

	save_commit_buffer = 0;

	for (ref = *refs; ref; ref = ref->next) {
		struct object *o;

		if (!has_object_file(&ref->old_oid))
			continue;

		o = parse_object(&ref->old_oid);
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

	if (!args->deepen) {
		for_each_ref(mark_complete_oid, NULL);
		for_each_cached_alternate(mark_alternate_complete);
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
		const struct object_id *remote = &ref->old_oid;
		struct object *o;

		o = lookup_object(remote->hash);
		if (!o || !(o->flags & COMPLETE)) {
			retval = 0;
			print_verbose(args, "want %s (%s)", oid_to_hex(remote),
				      ref->name);
			continue;
		}
		print_verbose(args, _("already have %s (%s)"), oid_to_hex(remote),
			      ref->name);
	}
	return retval;
}