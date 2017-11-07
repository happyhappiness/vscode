static int builtin_diff_combined(struct rev_info *revs,
				 int argc, const char **argv,
				 struct object_array_entry *ent,
				 int ents)
{
	struct sha1_array parents = SHA1_ARRAY_INIT;
	int i;

	if (argc > 1)
		usage(builtin_diff_usage);

	if (!revs->dense_combined_merges && !revs->combine_merges)
		revs->dense_combined_merges = revs->combine_merges = 1;
	for (i = 1; i < ents; i++)
		sha1_array_append(&parents, ent[i].item->oid.hash);
	diff_tree_combined(ent[0].item->oid.hash, &parents,
			   revs->dense_combined_merges, revs);
	sha1_array_clear(&parents);
	return 0;
}