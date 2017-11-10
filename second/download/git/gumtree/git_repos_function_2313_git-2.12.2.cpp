int remove_dir_recursively(struct strbuf *path, int flag)
{
	return remove_dir_recurse(path, flag, NULL);
}