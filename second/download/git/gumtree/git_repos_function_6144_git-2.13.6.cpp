static void handle_fetch_head(struct commit_list **remotes, struct strbuf *merge_names)
{
	const char *filename;
	int fd, pos, npos;
	struct strbuf fetch_head_file = STRBUF_INIT;

	if (!merge_names)
		merge_names = &fetch_head_file;

	filename = git_path_fetch_head();
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		die_errno(_("could not open '%s' for reading"), filename);

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
		}
		remotes = &commit_list_insert(commit, remotes)->next;
	}

	if (merge_names == &fetch_head_file)
		strbuf_release(&fetch_head_file);
}