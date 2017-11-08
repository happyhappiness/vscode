static int append_oid_to_argv(const struct object_id *oid, void *data)
{
	struct argv_array *argv = data;
	argv_array_push(argv, oid_to_hex(oid));
	return 0;
}