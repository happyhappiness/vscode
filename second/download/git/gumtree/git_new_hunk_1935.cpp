	const char *symref_target;
	struct string_list_item *item;
	unsigned char unused[20];

	if ((flag & REF_ISSYMREF) == 0)
		return 0;
	symref_target = resolve_ref_unsafe(refname, 0, unused, &flag);
	if (!symref_target || (flag & REF_ISSYMREF) == 0)
		die("'%s' is a symref but it is not?", refname);
	item = string_list_append(cb_data, refname);
	item->util = xstrdup(symref_target);
	return 0;
}
