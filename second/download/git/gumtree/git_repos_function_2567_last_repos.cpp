static const char *unquote_quoted_string(struct strbuf *outbuf, const char *in)
{
	int c;
	int take_next_literally = 0;

	while ((c = *in++) != 0) {
		if (take_next_literally == 1) {
			take_next_literally = 0;
		} else {
			switch (c) {
			case '\\':
				take_next_literally = 1;
				continue;
			case '"':
				return in;
			}
		}

		strbuf_addch(outbuf, c);
	}

	return in;
}