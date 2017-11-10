int sha1_array_lookup(struct sha1_array *array, const unsigned char *sha1)
{
	if (!array->sorted)
		sha1_array_sort(array);
	return sha1_pos(sha1, array->sha1, array->nr, sha1_access);
}