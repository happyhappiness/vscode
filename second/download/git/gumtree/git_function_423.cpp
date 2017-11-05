static int merge_one_change(struct notes_merge_options *o,
			    struct notes_merge_pair *p, struct notes_tree *t)
{
	/*
	 * Return 0 if change is successfully resolved (stored in notes_tree).
	 * Return 1 is change results in a conflict (NOT stored in notes_tree,
	 * but instead written to NOTES_MERGE_WORKTREE with conflict markers).
	 */
	switch (o->strategy) {
	case NOTES_MERGE_RESOLVE_MANUAL:
		return merge_one_change_manual(o, p, t);
	case NOTES_MERGE_RESOLVE_OURS:
		if (o->verbosity >= 2)
			printf("Using local notes for %s\n",
						sha1_to_hex(p->obj));
		/* nothing to do */
		return 0;
	case NOTES_MERGE_RESOLVE_THEIRS:
		if (o->verbosity >= 2)
			printf("Using remote notes for %s\n",
						sha1_to_hex(p->obj));
		if (add_note(t, p->obj, p->remote, combine_notes_overwrite))
			die("BUG: combine_notes_overwrite failed");
		return 0;
	case NOTES_MERGE_RESOLVE_UNION:
		if (o->verbosity >= 2)
			printf("Concatenating local and remote notes for %s\n",
							sha1_to_hex(p->obj));
		if (add_note(t, p->obj, p->remote, combine_notes_concatenate))
			die("failed to concatenate notes "
			    "(combine_notes_concatenate)");
		return 0;
	case NOTES_MERGE_RESOLVE_CAT_SORT_UNIQ:
		if (o->verbosity >= 2)
			printf("Concatenating unique lines in local and remote "
				"notes for %s\n", sha1_to_hex(p->obj));
		if (add_note(t, p->obj, p->remote, combine_notes_cat_sort_uniq))
			die("failed to concatenate notes "
			    "(combine_notes_cat_sort_uniq)");
		return 0;
	}
	die("Unknown strategy (%i).", o->strategy);
}