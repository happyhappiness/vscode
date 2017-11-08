void add_exclude_file(const char *fname, int fatal, int include)
{
	if (!fname || !*fname) return;

	exclude_list = make_exclude_list(fname,exclude_list,fatal,include);
}