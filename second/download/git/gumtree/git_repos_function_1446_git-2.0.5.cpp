int fsck_object(struct object *obj, int strict, fsck_error error_func)
{
	if (!obj)
		return error_func(obj, FSCK_ERROR, "no valid object to fsck");

	if (obj->type == OBJ_BLOB)
		return 0;
	if (obj->type == OBJ_TREE)
		return fsck_tree((struct tree *) obj, strict, error_func);
	if (obj->type == OBJ_COMMIT)
		return fsck_commit((struct commit *) obj, error_func);
	if (obj->type == OBJ_TAG)
		return fsck_tag((struct tag *) obj, error_func);

	return error_func(obj, FSCK_ERROR, "unknown type '%d' (internal fsck error)",
			  obj->type);
}