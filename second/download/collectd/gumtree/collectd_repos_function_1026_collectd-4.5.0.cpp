int TC_RENAME_CHAIN(const IPT_CHAINLABEL oldname,
		    const IPT_CHAINLABEL newname,
		    TC_HANDLE_T *handle)
{
	struct chain_head *c;
	iptc_fn = TC_RENAME_CHAIN;

	/* find_label doesn't cover built-in targets: DROP, ACCEPT,
           QUEUE, RETURN. */
	if (iptcc_find_label(newname, *handle)
	    || strcmp(newname, LABEL_DROP) == 0
	    || strcmp(newname, LABEL_ACCEPT) == 0
	    || strcmp(newname, LABEL_QUEUE) == 0
	    || strcmp(newname, LABEL_RETURN) == 0) {
		errno = EEXIST;
		return 0;
	}

	if (!(c = iptcc_find_label(oldname, *handle))
	    || TC_BUILTIN(oldname, *handle)) {
		errno = ENOENT;
		return 0;
	}

	if (strlen(newname)+1 > sizeof(IPT_CHAINLABEL)) {
		errno = EINVAL;
		return 0;
	}

	strncpy(c->name, newname, sizeof(IPT_CHAINLABEL));
	
	set_changed(*handle);

	return 1;
}