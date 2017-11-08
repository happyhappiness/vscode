static int string_list_df_name_compare(const char *one, const char *two)
{
	int onelen = strlen(one);
	int twolen = strlen(two);
	/*
	 * Here we only care that entries for D/F conflicts are
	 * adjacent, in particular with the file of the D/F conflict
	 * appearing before files below the corresponding directory.
	 * The order of the rest of the list is irrelevant for us.
	 *
	 * To achieve this, we sort with df_name_compare and provide
	 * the mode S_IFDIR so that D/F conflicts will sort correctly.
	 * We use the mode S_IFDIR for everything else for simplicity,
	 * since in other cases any changes in their order due to
	 * sorting cause no problems for us.
	 */
	int cmp = df_name_compare(one, onelen, S_IFDIR,
				  two, twolen, S_IFDIR);
	/*
	 * Now that 'foo' and 'foo/bar' compare equal, we have to make sure
	 * that 'foo' comes before 'foo/bar'.
	 */
	if (cmp)
		return cmp;
	return onelen - twolen;
}