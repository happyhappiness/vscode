static void sha1_array_sort(struct sha1_array *array)
{
	qsort(array->sha1, array->nr, sizeof(*array->sha1), void_hashcmp);
	array->sorted = 1;
}