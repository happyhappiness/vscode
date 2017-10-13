static void write_cherry_pick_head(struct commit *commit, const char *pseudoref)
{
	const char *filename;
	int fd;
	struct strbuf buf = STRBUF_INIT;

	strbuf_addf(&buf, "%s\n", sha1_to_hex(commit->object.sha1));

	filename = git_path("%s", pseudoref);
	fd = open(filename, O_WRONLY | O_CREAT, 0666);
	if (fd < 0)
		die_errno(_("Could not open '%s' for writing"), filename);
	if (write_in_full(fd, buf.buf, buf.len) != buf.len || close(fd))
		die_errno(_("Could not write to '%s'"), filename);
	strbuf_release(&buf);
}