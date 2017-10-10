	if (strbuf_read(merge_names, fd, 0) < 0)
		die_errno(_("could not read '%s'"), filename);
	if (close(fd) < 0)
		die_errno(_("could not close '%s'"), filename);

	for (pos = 0; pos < merge_names->len; pos = npos) {
		struct object_id oid;
		char *ptr;
		struct commit *commit;

		ptr = strchr(merge_names->buf + pos, '\n');
		if (ptr)
			npos = ptr - merge_names->buf + 1;
		else
			npos = merge_names->len;

		if (npos - pos < GIT_SHA1_HEXSZ + 2 ||
		    get_oid_hex(merge_names->buf + pos, &oid))
			commit = NULL; /* bad */
		else if (memcmp(merge_names->buf + pos + GIT_SHA1_HEXSZ, "\t\t", 2))
			continue; /* not-for-merge */
		else {
			char saved = merge_names->buf[pos + GIT_SHA1_HEXSZ];
			merge_names->buf[pos + GIT_SHA1_HEXSZ] = '\0';
			commit = get_merge_parent(merge_names->buf + pos);
			merge_names->buf[pos + GIT_SHA1_HEXSZ] = saved;
		}
		if (!commit) {
			if (ptr)
				*ptr = '\0';
			die(_("not something we can merge in %s: %s"),
			    filename, merge_names->buf + pos);
