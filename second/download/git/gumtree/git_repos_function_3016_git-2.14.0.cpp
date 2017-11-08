static int add_recent_packed(const struct object_id *oid,
			     struct packed_git *p, uint32_t pos,
			     void *data)
{
	struct object *obj = lookup_object(oid->hash);

	if (obj && obj->flags & SEEN)
		return 0;
	add_recent_object(oid, p->mtime, data);
	return 0;
}