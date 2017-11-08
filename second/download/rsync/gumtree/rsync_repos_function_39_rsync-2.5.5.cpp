void add_exclude(const char *pattern, int include)
{
	add_exclude_list(pattern,&exclude_list, include);
}