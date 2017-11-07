int cache_name_stage_compare(const char *name1, int len1, int stage1, const char *name2, int len2, int stage2)
{
	int len = len1 < len2 ? len1 : len2;
	int cmp;

	cmp = memcmp(name1, name2, len);
	if (cmp)
		return cmp;
	if (len1 < len2)
		return -1;
	if (len1 > len2)
		return 1;

	if (stage1 < stage2)
		return -1;
	if (stage1 > stage2)
		return 1;
	return 0;
}