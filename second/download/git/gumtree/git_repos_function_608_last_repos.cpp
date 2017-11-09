void ref_array_sort(struct ref_sorting *sorting, struct ref_array *array)
{
	QSORT_S(array->items, array->nr, compare_refs, sorting);
}