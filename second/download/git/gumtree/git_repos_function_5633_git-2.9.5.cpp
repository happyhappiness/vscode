static void write_merge_msg(struct strbuf *msg)
{
	const char *filename = git_path_merge_msg();
	int fd = open(filename, O_WRONLY | O_CREAT, 0666);
	if (fd < 0)
		die_errno(_("Could not open '%s' for writing"),
			  filename);
	if (write_in_full(fd, msg->buf, msg->len) != msg->len)
		die_errno(_("Could not write to '%s'"), filename);
	close(fd);
}