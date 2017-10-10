	if (!strcmp(new->name, "HEAD") && !new->path && !opts->force_detach) {
		/* Nothing to do. */
	} else if (opts->force_detach || !new->path) {	/* No longer on any branch. */
		update_ref(msg.buf, "HEAD", new->commit->object.oid.hash, NULL,
			   REF_NODEREF, UPDATE_REFS_DIE_ON_ERR);
		if (!opts->quiet) {
			if (old->path && advice_detached_head)
				detach_advice(new->name);
			describe_detached_head(_("HEAD is now at"), new->commit);
		}
	} else if (new->path) {	/* Switch branches. */
		if (create_symref("HEAD", new->path, msg.buf) < 0)
			die(_("unable to update HEAD"));
