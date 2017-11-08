static void free_exclude(struct exclude_struct *ex)
{
	free(ex->pattern);
	memset(ex,0,sizeof(*ex));
	free(ex);
}