void add_exclude_file(char *fname,int fatal)
{
	if (!fname || !*fname) return;

	exclude_list = make_exclude_list(fname,exclude_list,fatal);
}