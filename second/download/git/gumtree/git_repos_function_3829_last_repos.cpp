static struct commit *get_ref(const struct object_id *oid, const char *name)
{
	struct object *object;

	object = deref_tag(parse_object(oid), name, strlen(name));
	if (!object)
		return NULL;
	if (object->type == OBJ_TREE)
		return make_virtual_commit((struct tree*)object, name);
	if (object->type != OBJ_COMMIT)
		return NULL;
	if (parse_commit((struct commit *)object))
		return NULL;
	return (struct commit *)object;
}