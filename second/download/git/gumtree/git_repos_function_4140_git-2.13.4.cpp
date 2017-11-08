static int collect_ambiguous(const struct object_id *oid, void *data)
{
	oid_array_append(data, oid);
	return 0;
}