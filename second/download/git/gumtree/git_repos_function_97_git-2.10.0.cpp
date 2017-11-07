const char *skip_blank_lines(const char *msg)
{
	for (;;) {
		int linelen = get_one_line(msg);
		int ll = linelen;
		if (!linelen)
			break;
		if (!is_blank_line(msg, &ll))
			break;
		msg += linelen;
	}
	return msg;
}