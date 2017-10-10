			if (oidcmp(&o[0].item->oid, &o[1].item->oid) == 0)
				return 0;
		}
		get_patch_ids(&rev, &ids);
	}

	if (!use_stdout)
		realstdout = xfdopen(xdup(1), "w");

	if (prepare_revision_walk(&rev))
		die(_("revision walk setup failed"));
	rev.boundary = 1;
	while ((commit = get_revision(&rev)) != NULL) {
		if (commit->object.flags & BOUNDARY) {
			boundary_count++;
