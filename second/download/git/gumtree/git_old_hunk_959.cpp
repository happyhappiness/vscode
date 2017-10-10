		int flag = 0;
		struct object_id oid;

		read_ref_full(item->string, RESOLVE_REF_READING, oid.hash, &flag);
		if (!(flag & REF_ISSYMREF))
			continue;
		if (delete_ref(item->string, NULL, REF_NODEREF))
			die(_("deleting '%s' failed"), item->string);
	}
	for (i = 0; i < remote_branches.nr; i++) {
		struct string_list_item *item = remote_branches.items + i;

		if (item->util)
