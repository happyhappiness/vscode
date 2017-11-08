static int parse_file_arg(const struct option *opt, const char *arg, int unset)
{
	struct msg_arg *msg = opt->value;

	if (msg->buf.len)
		strbuf_addch(&(msg->buf), '\n');
	if (!strcmp(arg, "-")) {
		if (strbuf_read(&(msg->buf), 0, 1024) < 0)
			die_errno(_("cannot read '%s'"), arg);
	} else if (strbuf_read_file(&(msg->buf), arg, 1024) < 0)
		die_errno(_("could not open or read '%s'"), arg);
	stripspace(&(msg->buf), 0);

	msg->given = 1;
	return 0;
}