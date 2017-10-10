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
