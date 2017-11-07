static void add_mapping(struct string_list *map,
			char *new_name, char *new_email,
			char *old_name, char *old_email)
{
	struct mailmap_entry *me;
	struct string_list_item *item;

	if (old_email == NULL) {
		old_email = new_email;
		new_email = NULL;
	}

	item = string_list_insert(map, old_email);
	if (item->util) {
		me = (struct mailmap_entry *)item->util;
	} else {
		me = xcalloc(1, sizeof(struct mailmap_entry));
		me->namemap.strdup_strings = 1;
		me->namemap.cmp = namemap_cmp;
		item->util = me;
	}

	if (old_name == NULL) {
		debug_mm("mailmap: adding (simple) entry for '%s'\n", old_email);

		/* Replace current name and new email for simple entry */
		if (new_name) {
			free(me->name);
			me->name = xstrdup(new_name);
		}
		if (new_email) {
			free(me->email);
			me->email = xstrdup(new_email);
		}
	} else {
		struct mailmap_info *mi = xcalloc(1, sizeof(struct mailmap_info));
		debug_mm("mailmap: adding (complex) entry for '%s'\n", old_email);
		mi->name = xstrdup_or_null(new_name);
		mi->email = xstrdup_or_null(new_email);
		string_list_insert(&me->namemap, old_name)->util = mi;
	}

	debug_mm("mailmap:  '%s' <%s> -> '%s' <%s>\n",
		 debug_str(old_name), old_email,
		 debug_str(new_name), debug_str(new_email));
}