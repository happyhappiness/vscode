static int add_oid_to_argv(const struct object_id *oid, void *data)
{
	argv_array_push(data, oid_to_hex(oid));
	return 0;
}