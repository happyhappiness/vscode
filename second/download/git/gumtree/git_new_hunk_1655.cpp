	/*
	 * Verify that the remote and refspec can be propagated to all
	 * submodules.  This check can be skipped if the remote and refspec
	 * won't be propagated due to the remote being unconfigured (e.g. a URL
	 * instead of a remote name).
	 */
	if (remote->origin != REMOTE_UNCONFIGURED) {
		char *head;
		struct object_id head_oid;

		head = resolve_refdup("HEAD", 0, head_oid.hash, NULL);
		if (!head)
			die(_("Failed to resolve HEAD as a valid ref."));

		for (i = 0; i < needs_pushing.nr; i++)
			submodule_push_check(needs_pushing.items[i].string,
					     head, remote,
					     refspec, refspec_nr);
		free(head);
	}

	/* Actually push the submodules */
	for (i = 0; i < needs_pushing.nr; i++) {
		const char *path = needs_pushing.items[i].string;
		fprintf(stderr, "Pushing submodule '%s'\n", path);
		if (!push_submodule(path, remote, refspec, refspec_nr,
