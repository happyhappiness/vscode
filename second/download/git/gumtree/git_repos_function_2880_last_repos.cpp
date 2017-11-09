static int add_ref_decoration(const char *refname, const struct object_id *oid,
			      int flags, void *cb_data)
{
	struct object *obj;
	enum decoration_type type = DECORATION_NONE;

	assert(cb_data == NULL);

	if (starts_with(refname, git_replace_ref_base)) {
		struct object_id original_oid;
		if (!check_replace_refs)
			return 0;
		if (get_oid_hex(refname + strlen(git_replace_ref_base),
				&original_oid)) {
			warning("invalid replace ref %s", refname);
			return 0;
		}
		obj = parse_object(&original_oid);
		if (obj)
			add_name_decoration(DECORATION_GRAFTED, "replaced", obj);
		return 0;
	}

	obj = parse_object(oid);
	if (!obj)
		return 0;

	if (starts_with(refname, "refs/heads/"))
		type = DECORATION_REF_LOCAL;
	else if (starts_with(refname, "refs/remotes/"))
		type = DECORATION_REF_REMOTE;
	else if (starts_with(refname, "refs/tags/"))
		type = DECORATION_REF_TAG;
	else if (!strcmp(refname, "refs/stash"))
		type = DECORATION_REF_STASH;
	else if (!strcmp(refname, "HEAD"))
		type = DECORATION_REF_HEAD;

	add_name_decoration(type, refname, obj);
	while (obj->type == OBJ_TAG) {
		obj = ((struct tag *)obj)->tagged;
		if (!obj)
			break;
		if (!obj->parsed)
			parse_object(&obj->oid);
		add_name_decoration(DECORATION_REF_TAG, refname, obj);
	}
	return 0;
}