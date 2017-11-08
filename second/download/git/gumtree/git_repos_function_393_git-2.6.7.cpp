void sha1_array_append(struct sha1_array *array, const unsigned char *sha1)
{
	ALLOC_GROW(array->sha1, array->nr + 1, array->alloc);
	hashcpy(array->sha1[array->nr++], sha1);
	array->sorted = 0;
}