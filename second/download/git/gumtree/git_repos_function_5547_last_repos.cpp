static int show_independent(struct commit **rev,
			    int num_rev,
			    char **ref_name,
			    unsigned int *rev_mask)
{
	int i;

	for (i = 0; i < num_rev; i++) {
		struct commit *commit = rev[i];
		unsigned int flag = rev_mask[i];

		if (commit->object.flags == flag)
			puts(oid_to_hex(&commit->object.oid));
		commit->object.flags |= UNINTERESTING;
	}
	return 0;
}