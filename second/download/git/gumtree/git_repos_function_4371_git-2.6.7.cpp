static int name_ref(const char *path, const struct object_id *oid, int flags, void *cb_data)
{
	struct object *o = parse_object(oid->hash);
	struct name_ref_data *data = cb_data;
	int can_abbreviate_output = data->tags_only && data->name_only;
	int deref = 0;

	if (data->tags_only && !starts_with(path, "refs/tags/"))
		return 0;

	if (data->ref_filter) {
		switch (subpath_matches(path, data->ref_filter)) {
		case -1: /* did not match */
			return 0;
		case 0:  /* matched fully */
			break;
		default: /* matched subpath */
			can_abbreviate_output = 1;
			break;
		}
	}

	add_to_tip_table(oid->hash, path, can_abbreviate_output);

	while (o && o->type == OBJ_TAG) {
		struct tag *t = (struct tag *) o;
		if (!t->tagged)
			break; /* broken repository */
		o = parse_object(t->tagged->sha1);
		deref = 1;
	}
	if (o && o->type == OBJ_COMMIT) {
		struct commit *commit = (struct commit *)o;

		path = name_ref_abbrev(path, can_abbreviate_output);
		name_rev(commit, xstrdup(path), 0, 0, deref);
	}
	return 0;
}