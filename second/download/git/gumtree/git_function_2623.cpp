static int process_object(struct walker *walker, struct object *obj)
{
	if (obj->type == OBJ_COMMIT) {
		if (process_commit(walker, (struct commit *)obj))
			return -1;
		return 0;
	}
	if (obj->type == OBJ_TREE) {
		if (process_tree(walker, (struct tree *)obj))
			return -1;
		return 0;
	}
	if (obj->type == OBJ_BLOB) {
		return 0;
	}
	if (obj->type == OBJ_TAG) {
		if (process_tag(walker, (struct tag *)obj))
			return -1;
		return 0;
	}
	return error("Unable to determine requirements "
		     "of type %s for %s",
		     typename(obj->type), sha1_to_hex(obj->sha1));
}