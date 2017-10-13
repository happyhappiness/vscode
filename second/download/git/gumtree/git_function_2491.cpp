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
			      sha1_to_hex(obj->sha1),
			      typename(obj->type), typename(type));
		return NULL;
	}
}