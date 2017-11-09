static int disambiguate_treeish_only(const struct object_id *oid, void *cb_data_unused)
{
	struct object *obj;
	int kind;

	kind = sha1_object_info(oid->hash, NULL);
	if (kind == OBJ_TREE || kind == OBJ_COMMIT)
		return 1;
	if (kind != OBJ_TAG)
		return 0;

	/* We need to do this the hard way... */
	obj = deref_tag(parse_object(oid), NULL, 0);
	if (obj && (obj->type == OBJ_TREE || obj->type == OBJ_COMMIT))
		return 1;
	return 0;
}