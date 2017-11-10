void stage_updated_gitmodules(void)
{
	if (add_file_to_cache(".gitmodules", 0))
		die(_("staging updated .gitmodules failed"));
}