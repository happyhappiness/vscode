void sort_string_list(struct string_list *list)
{
	compare_for_qsort = list->cmp ? list->cmp : strcmp;
	qsort(list->items, list->nr, sizeof(*list->items), cmp_items);
}