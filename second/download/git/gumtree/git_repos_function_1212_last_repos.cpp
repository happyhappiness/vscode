void add_pending_oid(struct rev_info *revs, const char *name,
		      const struct object_id *oid, unsigned int flags)
{
	struct object *object = get_reference(revs, name, oid, flags);
	add_pending_object(revs, object, name);
}