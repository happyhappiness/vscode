static int fill_hashmap(mmfile_t *file1, mmfile_t *file2,
		xpparam_t const *xpp, xdfenv_t *env,
		struct hashmap *result,
		int line1, int count1, int line2, int count2)
{
	result->file1 = file1;
	result->file2 = file2;
	result->xpp = xpp;
	result->env = env;

	/* We know exactly how large we want the hash map */
	result->alloc = count1 * 2;
	result->entries = (struct entry *)
		xdl_malloc(result->alloc * sizeof(struct entry));
	if (!result->entries)
		return -1;
	memset(result->entries, 0, result->alloc * sizeof(struct entry));

	/* First, fill with entries from the first file */
	while (count1--)
		insert_record(line1++, result, 1);

	/* Then search for matches in the second file */
	while (count2--)
		insert_record(line2++, result, 2);

	return 0;
}