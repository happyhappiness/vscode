	int i, conflicts = 0;

	trace_printf("\tmerge_changes(num_changes = %i)\n", *num_changes);
	for (i = 0; i < *num_changes; i++) {
		struct notes_merge_pair *p = changes + i;
		trace_printf("\t\t%.7s: %.7s -> %.7s/%.7s\n",
		       oid_to_hex(&p->obj), oid_to_hex(&p->base),
		       oid_to_hex(&p->local),
		       oid_to_hex(&p->remote));

		if (!oidcmp(&p->base, &p->remote)) {
			/* no remote change; nothing to do */
			trace_printf("\t\t\tskipping (no remote change)\n");
		} else if (!oidcmp(&p->local, &p->remote)) {
			/* same change in local and remote; nothing to do */
			trace_printf("\t\t\tskipping (local == remote)\n");
		} else if (!oidcmp(&p->local, &uninitialized) ||
			   !oidcmp(&p->local, &p->base)) {
			/* no local change; adopt remote change */
			trace_printf("\t\t\tno local change, adopted remote\n");
			if (add_note(t, p->obj.hash, p->remote.hash,
				     combine_notes_overwrite))
				die("BUG: combine_notes_overwrite failed");
		} else {
			/* need file-level merge between local and remote */
			trace_printf("\t\t\tneed content-level merge\n");
			conflicts += merge_one_change(o, p, t);
