void string_list_sort(struct string_list *list)
{
	compare_for_qsort = list->cmp ? list->cmp : strcmp;
	qsort(list->items, list->nr, sizeof(*list->items), cmp_items);
}