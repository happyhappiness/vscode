static int save_files_dirs(const unsigned char *sha1,
		const char *base, int baselen, const char *path,
		unsigned int mode, int stage, void *context)
{
	int len = strlen(path);
	char *newpath = xmalloc(baselen + len + 1);
	struct merge_options *o = context;

	memcpy(newpath, base, baselen);
	memcpy(newpath + baselen, path, len);
	newpath[baselen + len] = '\0';

	if (S_ISDIR(mode))
		string_list_insert(&o->current_directory_set, newpath);
	else
		string_list_insert(&o->current_file_set, newpath);
	free(newpath);

	return (S_ISDIR(mode) ? READ_TREE_RECURSIVE : 0);
}