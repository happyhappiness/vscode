static void handle_fetch_head(struct commit_list **remotes, struct strbuf *merge_names)
{
	const char *filename;
	int fd, pos, npos;
	struct strbuf fetch_head_file = STRBUF_INIT;

	if (!merge_names)
		merge_names = &fetch_head_file;

	filename = git_path("FETCH_HEAD");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		die_errno(_("could not open '%s' for reading"), filename);

	if (strbuf_read(merge_names, fd, 0) < 0)
		die_errno(_("could not read '%s'"), filename);
	if (close(fd) < 0)
		die_errno(_("could not close '%s'"), filename);

	for (pos = 0; pos < merge_names->len; pos = npos) {
		unsigned char sha1[20];
		char *ptr;
		struct commit *commit;

		ptr = strchr(merge_names->buf + pos, '\n');
		if (ptr)
			npos = ptr - merge_names->buf + 1;
		else
			npos = merge_names->len;

		if (npos - pos < 40 + 2 ||
		    get_sha1_hex(merge_names->buf + pos, sha1))
			commit = NULL; /* bad */
		else if (memcmp(merge_names->buf + pos + 40, "\t\t", 2))
			continue; /* not-for-merge */
		else {
			char saved = merge_names->buf[pos + 40];
			merge_names->buf[pos + 40] = '\0';
			commit = get_merge_parent(merge_names->buf + pos);
			merge_names->buf[pos + 40] = saved;
		}
		if (!commit) {
			if (ptr)
				*ptr = '\0';
			die("not something we can merge in %s: %s",
			    filename, merge_names->buf + pos);
		}
		remotes = &commit_list_insert(commit, remotes)->next;
	}

	if (merge_names == &fetch_head_file)
		strbuf_release(&fetch_head_file);
}