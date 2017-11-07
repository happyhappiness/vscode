static int handle_one_ref(const char *path,
		const unsigned char *sha1, int flag, void *cb_data)
{
	struct commit_list **list = cb_data;
	struct object *object = parse_object(sha1);
	if (!object)
		return 0;
	if (object->type == OBJ_TAG) {
		object = deref_tag(object, path, strlen(path));
		if (!object)
			return 0;
	}
	if (object->type != OBJ_COMMIT)
		return 0;
	commit_list_insert_by_date((struct commit *)object, list);
	return 0;
}