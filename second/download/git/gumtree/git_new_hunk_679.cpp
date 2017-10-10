						  &size, NULL);
		grep_read_unlock();

		if (!data)
			die(_("unable to read tree (%s)"), oid_to_hex(&obj->oid));

		/* Use parent's name as base when recursing submodules */
		if (recurse_submodules && parent_basename)
			name = parent_basename;

		len = name ? strlen(name) : 0;
		strbuf_init(&base, PATH_MAX + len + 1);
		if (len) {
			strbuf_add(&base, name, len);
			strbuf_addch(&base, ':');
		}
