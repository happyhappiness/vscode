void ref_array_sort(struct ref_sorting *sorting, struct ref_array *array)
{
	ref_sorting = sorting;
	QSORT(array->items, array->nr, compare_refs);
}