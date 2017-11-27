static int cf_compare_string (const void *p1, const void *p2)
{
	return strcmp (*(const char **) p1, *(const char **) p2);
}