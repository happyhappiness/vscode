static int batch_packed_object(const struct object_id *oid,
			       struct packed_git *pack,
			       uint32_t pos,
			       void *data)
{
	oid_array_append(data, oid);
	return 0;
}