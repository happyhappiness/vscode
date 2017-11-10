static int cmp_items(const void *a, const void *b)
{
	const struct string_list_item *one = a;
	const struct string_list_item *two = b;
	return compare_for_qsort(one->string, two->string);
}