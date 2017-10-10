	if (add_pending_commit(upstream, &revs, UNINTERESTING))
		die(_("Unknown commit %s"), upstream);

	/* Don't say anything if head and upstream are the same. */
	if (revs.pending.nr == 2) {
		struct object_array_entry *o = revs.pending.objects;
		if (oidcmp(&o[0].item->oid, &o[1].item->oid) == 0)
			return 0;
	}

	get_patch_ids(&revs, &ids);

	if (limit && add_pending_commit(limit, &revs, UNINTERESTING))
