struct commit *get_merge_parent(const char *name)
{
	struct object *obj;
	struct commit *commit;
	unsigned char sha1[20];
	if (get_sha1(name, sha1))
		return NULL;
	obj = parse_object(sha1);
	commit = (struct commit *)peel_to_type(name, 0, obj, OBJ_COMMIT);
	if (commit && !commit->util) {
		struct merge_remote_desc *desc;
		desc = xmalloc(sizeof(*desc));
		desc->obj = obj;
		desc->name = strdup(name);
		commit->util = desc;
	}
	return commit;
}