static int builtin_diff_tree(struct rev_info *revs,
			     int argc, const char **argv,
			     struct object_array_entry *ent0,
			     struct object_array_entry *ent1)
{
	const unsigned char *(sha1[2]);
	int swap = 0;

	if (argc > 1)
		usage(builtin_diff_usage);

	/*
	 * We saw two trees, ent0 and ent1.  If ent1 is uninteresting,
	 * swap them.
	 */
	if (ent1->item->flags & UNINTERESTING)
		swap = 1;
	sha1[swap] = ent0->item->oid.hash;
	sha1[1 - swap] = ent1->item->oid.hash;
	diff_tree_sha1(sha1[0], sha1[1], "", &revs->diffopt);
	log_tree_diff_flush(revs);
	return 0;
}