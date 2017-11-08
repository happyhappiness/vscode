static int mark_loose_for_connectivity(const struct object_id *oid,
				       const char *path,
				       void *data)
{
	mark_object_for_connectivity(oid);
	return 0;
}