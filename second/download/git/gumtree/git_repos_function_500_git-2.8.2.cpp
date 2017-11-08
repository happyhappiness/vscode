void ref_array_sort(struct ref_sorting *sorting, struct ref_array *array)
{
	ref_sorting = sorting;
	qsort(array->items, array->nr, sizeof(struct ref_array_item *), compare_refs);
}