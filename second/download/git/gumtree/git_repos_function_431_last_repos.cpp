int oid_array_lookup(struct oid_array *array, const struct object_id *oid)
{
	if (!array->sorted)
		oid_array_sort(array);
	return sha1_pos(oid->hash, array->oid, array->nr, sha1_access);
}