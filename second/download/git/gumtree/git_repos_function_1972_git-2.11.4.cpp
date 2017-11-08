void string_list_sort(struct string_list *list)
{
	compare_for_qsort = list->cmp ? list->cmp : strcmp;
	QSORT(list->items, list->nr, cmp_items);
}