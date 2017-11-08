static int parse_msg_arg(const struct option *opt, const char *arg, int unset)
{
	struct msg_arg *msg = opt->value;

	strbuf_grow(&(msg->buf), strlen(arg) + 2);
	if (msg->buf.len)
		strbuf_addch(&(msg->buf), '\n');
	strbuf_addstr(&(msg->buf), arg);
	stripspace(&(msg->buf), 0);

	msg->given = 1;
	return 0;
}