int git_config_rename_section(const char *old_name, const char *new_name)
{
	return git_config_rename_section_in_file(NULL, old_name, new_name);
}