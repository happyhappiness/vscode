int name_compare(const char *name1, size_t len1, const char *name2, size_t len2)
{
	size_t min_len = (len1 < len2) ? len1 : len2;
	int cmp = memcmp(name1, name2, min_len);
	if (cmp)
		return cmp;
	if (len1 < len2)
		return -1;
	if (len1 > len2)
		return 1;
	return 0;
}