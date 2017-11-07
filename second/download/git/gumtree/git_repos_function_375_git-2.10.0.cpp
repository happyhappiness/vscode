void stat_validity_clear(struct stat_validity *sv)
{
	free(sv->sd);
	sv->sd = NULL;
}