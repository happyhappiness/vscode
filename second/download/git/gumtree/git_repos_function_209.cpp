static void free_combined_pair(struct diff_filepair *pair)
{
	free(pair->two);
	free(pair);
}