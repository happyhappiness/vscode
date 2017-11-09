int read_repository_format(struct repository_format *format, const char *path)
{
	memset(format, 0, sizeof(*format));
	format->version = -1;
	format->is_bare = -1;
	string_list_init(&format->unknown_extensions, 1);
	git_config_from_file(check_repo_format, path, format);
	return format->version;
}