static void finish_object(struct object *obj, const char *name, void *cb_data)
{
	struct rev_list_info *info = cb_data;
	if (obj->type == OBJ_BLOB && !has_sha1_file(obj->sha1))
		die("missing blob object '%s'", sha1_to_hex(obj->sha1));
	if (info->revs->verify_objects && !obj->parsed && obj->type != OBJ_COMMIT)
		parse_object(obj->sha1);
}