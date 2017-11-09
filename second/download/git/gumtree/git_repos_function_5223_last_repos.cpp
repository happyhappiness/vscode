static int compare_by_list(const void *a1, const void *a2)
{
	const struct string_list_item *i1 = a1, *i2 = a2;
	const struct string_list *l1 = i1->util, *l2 = i2->util;

	if (l1->nr < l2->nr)
		return 1;
	else if (l1->nr == l2->nr)
		return 0;
	else
		return -1;
}