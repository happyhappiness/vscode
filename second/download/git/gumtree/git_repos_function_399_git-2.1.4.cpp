static int find_exact_renames(struct diff_options *options)
{
	int i, renames = 0;
	struct hashmap file_table;

	/* Add all sources to the hash table */
	hashmap_init(&file_table, NULL, rename_src_nr);
	for (i = 0; i < rename_src_nr; i++)
		insert_file_table(&file_table, i, rename_src[i].p->one);

	/* Walk the destinations and find best source match */
	for (i = 0; i < rename_dst_nr; i++)
		renames += find_identical_files(&file_table, i, options);

	/* Free the hash data structure and entries */
	hashmap_free(&file_table, 1);

	return renames;
}