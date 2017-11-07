int cache_name_compare(const char *name1, int len1, const char *name2, int len2)
{
	return cache_name_stage_compare(name1, len1, 0, name2, len2, 0);
}