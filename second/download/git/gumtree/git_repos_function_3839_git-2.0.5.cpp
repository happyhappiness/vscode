static int has_string_in_work_tree(const char *path)
{
	struct stat st;
	return !lstat(path, &st);
}