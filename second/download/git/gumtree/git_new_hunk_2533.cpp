			append_strategy(&all_strategy[i]);

}

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

static void read_merge_msg(struct strbuf *msg)
{
	const char *filename = git_path_merge_msg();
	strbuf_reset(msg);
	if (strbuf_read_file(msg, filename, 0) < 0)
		die_errno(_("Could not read from '%s'"), filename);
}

static void write_merge_state(struct commit_list *);
