static int diff_tree_stdin(char *line)
{
	int len = strlen(line);
	struct object_id oid;
	struct object *obj;
	const char *p;

	if (!len || line[len-1] != '\n')
		return -1;
	line[len-1] = 0;
	if (parse_oid_hex(line, &oid, &p))
		return -1;
	obj = parse_object(&oid);
	if (!obj)
		return -1;
	if (obj->type == OBJ_COMMIT)
		return stdin_diff_commit((struct commit *)obj, p);
	if (obj->type == OBJ_TREE)
		return stdin_diff_trees((struct tree *)obj, p);
	error("Object %s is a %s, not a commit or tree",
	      oid_to_hex(&oid), typename(obj->type));
	return -1;
}