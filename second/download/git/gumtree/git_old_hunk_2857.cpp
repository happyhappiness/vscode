	const char *filename;
	int fd;
	struct commit_list *j;
	struct strbuf buf = STRBUF_INIT;

	for (j = remoteheads; j; j = j->next) {
		unsigned const char *sha1;
		struct commit *c = j->item;
		if (c->util && merge_remote_util(c)->obj) {
			sha1 = merge_remote_util(c)->obj->sha1;
		} else {
			sha1 = c->object.sha1;
		}
		strbuf_addf(&buf, "%s\n", sha1_to_hex(sha1));
	}
	filename = git_path_merge_head();
	fd = open(filename, O_WRONLY | O_CREAT, 0666);
	if (fd < 0)
		die_errno(_("Could not open '%s' for writing"), filename);
	if (write_in_full(fd, buf.buf, buf.len) != buf.len)
