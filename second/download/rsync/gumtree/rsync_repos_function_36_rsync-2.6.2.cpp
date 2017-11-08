static void free_exclude(struct exclude_struct *ex)
{
	free(ex->pattern);
	free(ex);
}