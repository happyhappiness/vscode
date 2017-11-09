int convert_to_working_tree(const char *path, const char *src, size_t len, struct strbuf *dst)
{
	return convert_to_working_tree_internal(path, src, len, dst, 0, NULL);
}