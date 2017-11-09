void *object_as_type(struct object *obj, enum object_type type, int quiet)
{
	if (obj->type == type)
		return obj;
	else if (obj->type == OBJ_NONE) {
		if (type == OBJ_COMMIT)
			((struct commit *)obj)->index = alloc_commit_index();
		obj->type = type;
		return obj;
	}
	else {
		if (!quiet)
			error("object %s is a %s, not a %s",
			      oid_to_hex(&obj->oid),
			      typename(obj->type), typename(type));
		return NULL;
	}
}