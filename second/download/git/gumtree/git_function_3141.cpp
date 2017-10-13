static void write_merge_state(struct commit_list *remoteheads)
{
	const char *filename;
	int fd;
	struct commit_list *j;
	struct strbuf buf = STRBUF_INIT;

	for (j = remoteheads; j; j = j->next) {
		struct object_id *oid;
		struct commit *c = j->item;
		if (c->util && merge_remote_util(c)->obj) {
			oid = &merge_remote_util(c)->obj->oid;
		} else {
			oid = &c->object.oid;
		}
		strbuf_addf(&buf, "%s\n", oid_to_hex(oid));
	}
	filename = git_path_merge_head();
	fd = open(filename, O_WRONLY | O_CREAT, 0666);
	if (fd < 0)
		die_errno(_("Could not open '%s' for writing"), filename);
	if (write_in_full(fd, buf.buf, buf.len) != buf.len)
		die_errno(_("Could not write to '%s'"), filename);
	close(fd);
	strbuf_addch(&merge_msg, '\n');
	write_merge_msg(&merge_msg);

	filename = git_path_merge_mode();
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		die_errno(_("Could not open '%s' for writing"), filename);
	strbuf_reset(&buf);
	if (fast_forward == FF_NO)
		strbuf_addf(&buf, "no-ff");
	if (write_in_full(fd, buf.buf, buf.len) != buf.len)
		die_errno(_("Could not write to '%s'"), filename);
	close(fd);
}