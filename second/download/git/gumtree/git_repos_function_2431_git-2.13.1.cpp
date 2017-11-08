static const char *unquote_comment(struct strbuf *outbuf, const char *in)
{
	int c;
	int take_next_litterally = 0;

	strbuf_addch(outbuf, '(');

	while ((c = *in++) != 0) {
		if (take_next_litterally == 1) {
			take_next_litterally = 0;
		} else {
			switch (c) {
			case '\\':
				take_next_litterally = 1;
				continue;
			case '(':
				in = unquote_comment(outbuf, in);
				continue;
			case ')':
				strbuf_addch(outbuf, ')');
				return in;
			}
		}

		strbuf_addch(outbuf, c);
	}

	return in;
}