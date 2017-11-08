static int update_info_refs(int force)
{
	char *path = git_pathdup("info/refs");
	int ret = update_info_file(path, generate_info_refs);
	free(path);
	return ret;
}