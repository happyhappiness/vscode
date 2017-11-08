static struct object *get_reference(struct rev_info *revs, const char *name,
				    const struct object_id *oid,
				    unsigned int flags)
{
	struct object *object;

	object = parse_object(oid);
	if (!object) {
		if (revs->ignore_missing)
			return object;
		die("bad object %s", name);
	}
	object->flags |= flags;
	return object;
}