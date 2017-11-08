int cache_name_stage_compare(const char *name1, int len1, int stage1, const char *name2, int len2, int stage2)
{
	int cmp;

	cmp = name_compare(name1, len1, name2, len2);
	if (cmp)
		return cmp;

	if (stage1 < stage2)
		return -1;
	if (stage1 > stage2)
		return 1;
	return 0;
}