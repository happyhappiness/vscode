int add_excludes_from_file_to_list(const char *fname, const char *base,
				   int baselen, struct exclude_list *el,
				   int check_index)
{
	return add_excludes(fname, base, baselen, el, check_index, NULL);
}