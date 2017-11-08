static void read_merge_msg(struct strbuf *msg)
{
	const char *filename = git_path_merge_msg();
	strbuf_reset(msg);
	if (strbuf_read_file(msg, filename, 0) < 0)
		die_errno(_("Could not read from '%s'"), filename);
}