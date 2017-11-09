int is_staging_gitmodules_ok(void)
{
	return !gitmodules_is_modified;
}