void ref_array_sort(struct ref_sorting *sorting, struct ref_array *array)
{
	ref_sorting = sorting;
	qsort(array->items, array->nr, sizeof(struct ref_array_item *), compare_refs);
}

static int hex1(char ch)
{
	if ('0' <= ch && ch <= '9')
		return ch - '0';
	else if ('a' <= ch && ch <= 'f')
		return ch - 'a' + 10;
