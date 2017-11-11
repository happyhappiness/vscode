static int merge_one_change_manual(struct notes_merge_options *o,
				   struct notes_merge_pair *p,
				   struct notes_tree *t)
{
	const char *lref = o->local_ref ? o->local_ref : "local version";
	const char *rref = o->remote_ref ? o->remote_ref : "remote version";

	trace_printf("\t\t\tmerge_one_change_manual(obj = %.7s, base = %.7s, "
	       "local = %.7s, remote = %.7s)\n",
	       sha1_to_hex(p->obj), sha1_to_hex(p->base),
	       sha1_to_hex(p->local), sha1_to_hex(p->remote));

	/* add "Conflicts:" section to commit message first time through */
	if (!o->has_worktree)
		strbuf_addstr(&(o->commit_msg), "\n\nConflicts:\n");

	strbuf_addf(&(o->commit_msg), "\t%s\n", sha1_to_hex(p->obj));

	if (o->verbosity >= 2)
		printf("Auto-merging notes for %s\n", sha1_to_hex(p->obj));
	check_notes_merge_worktree(o);
	if (is_null_sha1(p->local)) {
		/* D/F conflict, checkout p->remote */
		assert(!is_null_sha1(p->remote));
		if (o->verbosity >= 1)
			printf("CONFLICT (delete/modify): Notes for object %s "
				"deleted in %s and modified in %s. Version from %s "
				"left in tree.\n",
				sha1_to_hex(p->obj), lref, rref, rref);
		write_note_to_worktree(p->obj, p->remote);
	} else if (is_null_sha1(p->remote)) {
		/* D/F conflict, checkout p->local */
		assert(!is_null_sha1(p->local));
		if (o->verbosity >= 1)
			printf("CONFLICT (delete/modify): Notes for object %s "
				"deleted in %s and modified in %s. Version from %s "
				"left in tree.\n",
				sha1_to_hex(p->obj), rref, lref, lref);
		write_note_to_worktree(p->obj, p->local);
	} else {
		/* "regular" conflict, checkout result of ll_merge() */
		const char *reason = "content";
		if (is_null_sha1(p->base))
			reason = "add/add";
		assert(!is_null_sha1(p->local));
		assert(!is_null_sha1(p->remote));
		if (o->verbosity >= 1)
			printf("CONFLICT (%s): Merge conflict in notes for "
				"object %s\n", reason, sha1_to_hex(p->obj));
		ll_merge_in_worktree(o, p);
	}

	trace_printf("\t\t\tremoving from partial merge result\n");
	remove_note(t, p->obj);

	return 1;
}