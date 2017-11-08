static void sha1_array_sort(struct sha1_array *array)
{
	QSORT(array->sha1, array->nr, void_hashcmp);
	array->sorted = 1;
}