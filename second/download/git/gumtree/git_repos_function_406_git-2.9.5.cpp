void sha1_array_clear(struct sha1_array *array)
{
	free(array->sha1);
	array->sha1 = NULL;
	array->nr = 0;
	array->alloc = 0;
	array->sorted = 0;
}