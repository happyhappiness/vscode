static void sort_refs(struct ref_sort *sort, struct refinfo **refs, int num_refs)
{
	ref_sort = sort;
	qsort(refs, num_refs, sizeof(struct refinfo *), compare_refs);
}