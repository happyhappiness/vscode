static int merge_from_diffs(struct notes_merge_options *o,
			    const struct object_id *base,
			    const struct object_id *local,
			    const struct object_id *remote,
			    struct notes_tree *t)
{
	struct notes_merge_pair *changes;
	int num_changes, conflicts;

	trace_printf("\tmerge_from_diffs(base = %.7s, local = %.7s, "
	       "remote = %.7s)\n", oid_to_hex(base), oid_to_hex(local),
	       oid_to_hex(remote));

	changes = diff_tree_remote(o, base, remote, &num_changes);
	diff_tree_local(o, changes, num_changes, base, local);

	conflicts = merge_changes(o, changes, &num_changes, t);
	free(changes);

	if (o->verbosity >= 4)
		printf(t->dirty ?
		       "Merge result: %i unmerged notes and a dirty notes tree\n" :
		       "Merge result: %i unmerged notes and a clean notes tree\n",
		       conflicts);

	return conflicts ? -1 : 1;
}