static int mark_packed_for_connectivity(const struct object_id *oid,
					struct packed_git *pack,
					uint32_t pos,
					void *data)
{
	mark_object_for_connectivity(oid);
	return 0;
}