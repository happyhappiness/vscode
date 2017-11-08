static int append_loose_object(const struct object_id *oid, const char *path,
			       void *data)
{
	oid_array_append(data, oid);
	return 0;
}