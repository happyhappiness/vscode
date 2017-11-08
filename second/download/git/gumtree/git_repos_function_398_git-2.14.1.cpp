void stat_validity_clear(struct stat_validity *sv)
{
	FREE_AND_NULL(sv->sd);
}