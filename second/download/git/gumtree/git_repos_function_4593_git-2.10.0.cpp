static int compare_by_counter(const void *a1, const void *a2)
{
	const struct string_list_item *i1 = a1, *i2 = a2;
	return UTIL_TO_INT(i2) - UTIL_TO_INT(i1);
}