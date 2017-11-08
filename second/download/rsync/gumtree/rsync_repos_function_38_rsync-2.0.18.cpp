void add_exclude(char *pattern, int include)
{
	add_exclude_list(pattern,&exclude_list, include);
}