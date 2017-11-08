void sha1_array_for_each_unique(struct sha1_array *array,
				for_each_sha1_fn fn,
				void *data)
{
	int i;

	if (!array->sorted)
		sha1_array_sort(array);

	for (i = 0; i < array->nr; i++) {
		if (i > 0 && !hashcmp(array->sha1[i], array->sha1[i-1]))
			continue;
		fn(array->sha1[i], data);
	}
}