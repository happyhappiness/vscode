		assert(!is_null_oid(&p->remote));
		if (o->verbosity >= 1)
			printf("CONFLICT (delete/modify): Notes for object %s "
				"deleted in %s and modified in %s. Version from %s "
				"left in tree.\n",
				oid_to_hex(&p->obj), lref, rref, rref);
		write_note_to_worktree(p->obj.hash, p->remote.hash);
	} else if (is_null_oid(&p->remote)) {
		/* D/F conflict, checkout p->local */
		assert(!is_null_oid(&p->local));
		if (o->verbosity >= 1)
			printf("CONFLICT (delete/modify): Notes for object %s "
				"deleted in %s and modified in %s. Version from %s "
				"left in tree.\n",
				oid_to_hex(&p->obj), rref, lref, lref);
		write_note_to_worktree(p->obj.hash, p->local.hash);
	} else {
		/* "regular" conflict, checkout result of ll_merge() */
		const char *reason = "content";
		if (is_null_oid(&p->base))
			reason = "add/add";
		assert(!is_null_oid(&p->local));
