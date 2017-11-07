static void print_bases(struct base_tree_info *bases)
{
	int i;

	/* Only do this once, either for the cover or for the first one */
	if (is_null_oid(&bases->base_commit))
		return;

	/* Show the base commit */
	printf("base-commit: %s\n", oid_to_hex(&bases->base_commit));

	/* Show the prerequisite patches */
	for (i = bases->nr_patch_id - 1; i >= 0; i--)
		printf("prerequisite-patch-id: %s\n", oid_to_hex(&bases->patch_id[i]));

	free(bases->patch_id);
	bases->nr_patch_id = 0;
	bases->alloc_patch_id = 0;
	oidclr(&bases->base_commit);
}