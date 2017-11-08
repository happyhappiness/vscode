static int add_sha1_to_array(const char *ref, const struct object_id *oid,
			     int flags, void *data)
{
	oid_array_append(data, oid);
	return 0;
}