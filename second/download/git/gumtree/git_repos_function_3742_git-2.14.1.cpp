static int append_oid_to_array(const char *ref, const struct object_id *oid,
			       int flags, void *data)
{
	struct oid_array *array = data;
	oid_array_append(array, oid);
	return 0;
}