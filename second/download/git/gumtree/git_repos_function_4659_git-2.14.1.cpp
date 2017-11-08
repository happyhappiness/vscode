static void parse_pathspec_attr_match(struct pathspec_item *item, const char *value)
{
	struct string_list_item *si;
	struct string_list list = STRING_LIST_INIT_DUP;

	if (item->attr_check || item->attr_match)
		die(_("Only one 'attr:' specification is allowed."));

	if (!value || !*value)
		die(_("attr spec must not be empty"));

	string_list_split(&list, value, ' ', -1);
	string_list_remove_empty_items(&list, 0);

	item->attr_check = attr_check_alloc();
	item->attr_match = xcalloc(list.nr, sizeof(struct attr_match));

	for_each_string_list_item(si, &list) {
		size_t attr_len;
		char *attr_name;
		const struct git_attr *a;

		int j = item->attr_match_nr++;
		const char *attr = si->string;
		struct attr_match *am = &item->attr_match[j];

		switch (*attr) {
		case '!':
			am->match_mode = MATCH_UNSPECIFIED;
			attr++;
			attr_len = strlen(attr);
			break;
		case '-':
			am->match_mode = MATCH_UNSET;
			attr++;
			attr_len = strlen(attr);
			break;
		default:
			attr_len = strcspn(attr, "=");
			if (attr[attr_len] != '=')
				am->match_mode = MATCH_SET;
			else {
				const char *v = &attr[attr_len + 1];
				am->match_mode = MATCH_VALUE;
				am->value = attr_value_unescape(v);
			}
			break;
		}

		attr_name = xmemdupz(attr, attr_len);
		a = git_attr(attr_name);
		if (!a)
			die(_("invalid attribute name %s"), attr_name);

		attr_check_append(item->attr_check, a);

		free(attr_name);
	}

	if (item->attr_check->nr != item->attr_match_nr)
		die("BUG: should have same number of entries");

	string_list_clear(&list, 0);
}