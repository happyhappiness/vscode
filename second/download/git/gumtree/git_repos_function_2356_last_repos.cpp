static const char *get_home_gitattributes(void)
{
	if (!git_attributes_file)
		git_attributes_file = xdg_config_home("attributes");

	return git_attributes_file;
}