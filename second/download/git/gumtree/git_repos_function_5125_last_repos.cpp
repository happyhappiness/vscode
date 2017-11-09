static int name_ref(const char *path, const struct object_id *oid, int flags, void *cb_data)
{
	struct object *o = parse_object(oid);
	struct name_ref_data *data = cb_data;
	int can_abbreviate_output = data->tags_only && data->name_only;
	int deref = 0;
	timestamp_t taggerdate = TIME_MAX;

	if (data->tags_only && !starts_with(path, "refs/tags/"))
		return 0;

	if (data->exclude_filters.nr) {
		struct string_list_item *item;

		for_each_string_list_item(item, &data->exclude_filters) {
			if (subpath_matches(path, item->string) >= 0)
				return 0;
		}
	}

	if (data->ref_filters.nr) {
		struct string_list_item *item;
		int matched = 0;

		/* See if any of the patterns match. */
		for_each_string_list_item(item, &data->ref_filters) {
			/*
			 * Check all patterns even after finding a match, so
			 * that we can see if a match with a subpath exists.
			 * When a user asked for 'refs/tags/v*' and 'v1.*',
			 * both of which match, the user is showing her
			 * willingness to accept a shortened output by having
			 * the 'v1.*' in the acceptable refnames, so we
			 * shouldn't stop when seeing 'refs/tags/v1.4' matches
			 * 'refs/tags/v*'.  We should show it as 'v1.4'.
			 */
			switch (subpath_matches(path, item->string)) {
			case -1: /* did not match */
				break;
			case 0: /* matched fully */
				matched = 1;
				break;
			default: /* matched subpath */
				matched = 1;
				can_abbreviate_output = 1;
				break;
			}
		}

		/* If none of the patterns matched, stop now */
		if (!matched)
			return 0;
	}

	add_to_tip_table(oid, path, can_abbreviate_output);

	while (o && o->type == OBJ_TAG) {
		struct tag *t = (struct tag *) o;
		if (!t->tagged)
			break; /* broken repository */
		o = parse_object(&t->tagged->oid);
		deref = 1;
		taggerdate = t->date;
	}
	if (o && o->type == OBJ_COMMIT) {
		struct commit *commit = (struct commit *)o;
		int from_tag = starts_with(path, "refs/tags/");

		if (taggerdate == ULONG_MAX)
			taggerdate = ((struct commit *)o)->date;
		path = name_ref_abbrev(path, can_abbreviate_output);
		name_rev(commit, xstrdup(path), taggerdate, 0, 0,
			 from_tag, deref);
	}
	return 0;
}