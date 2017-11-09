static int builtin_diff_tree(struct rev_info *revs,
			     int argc, const char **argv,
			     struct object_array_entry *ent0,
			     struct object_array_entry *ent1)
{
	const struct object_id *(oid[2]);
	int swap = 0;

	if (argc > 1)
		usage(builtin_diff_usage);

	/*
	 * We saw two trees, ent0 and ent1.  If ent1 is uninteresting,
	 * swap them.
	 */
	if (ent1->item->flags & UNINTERESTING)
		swap = 1;
	oid[swap] = &ent0->item->oid;
	oid[1 - swap] = &ent1->item->oid;
	diff_tree_oid(oid[0], oid[1], "", &revs->diffopt);
	log_tree_diff_flush(revs);
	return 0;
}