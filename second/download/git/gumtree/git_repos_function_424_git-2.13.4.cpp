int oid_array_for_each_unique(struct oid_array *array,
				for_each_oid_fn fn,
				void *data)
{
	int i;

	if (!array->sorted)
		oid_array_sort(array);

	for (i = 0; i < array->nr; i++) {
		int ret;
		if (i > 0 && !oidcmp(array->oid + i, array->oid + i - 1))
			continue;
		ret = fn(array->oid + i, data);
		if (ret)
			return ret;
	}
	return 0;
}