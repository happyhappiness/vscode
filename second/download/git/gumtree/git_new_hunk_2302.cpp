
const struct name_decoration *get_name_decoration(const struct object *obj)
{
	return lookup_decoration(&name_decoration, obj);
}

static int add_ref_decoration(const char *refname, const struct object_id *oid,
			      int flags, void *cb_data)
{
	struct object *obj;
	enum decoration_type type = DECORATION_NONE;

	assert(cb_data == NULL);

	if (starts_with(refname, "refs/replace/")) {
		struct object_id original_oid;
		if (!check_replace_refs)
			return 0;
		if (get_oid_hex(refname + 13, &original_oid)) {
			warning("invalid replace ref %s", refname);
			return 0;
		}
		obj = parse_object(original_oid.hash);
		if (obj)
			add_name_decoration(DECORATION_GRAFTED, "replaced", obj);
		return 0;
	}

	obj = parse_object(oid->hash);
	if (!obj)
		return 0;

	if (starts_with(refname, "refs/heads/"))
		type = DECORATION_REF_LOCAL;
	else if (starts_with(refname, "refs/remotes/"))
