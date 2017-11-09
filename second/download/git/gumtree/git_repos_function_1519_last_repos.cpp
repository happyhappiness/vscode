static char *url_decode_internal(const char **query, int len,
				 const char *stop_at, struct strbuf *out,
				 int decode_plus)
{
	const char *q = *query;

	while (len) {
		unsigned char c = *q;

		if (!c)
			break;
		if (stop_at && strchr(stop_at, c)) {
			q++;
			len--;
			break;
		}

		if (c == '%') {
			int val = hex2chr(q + 1);
			if (0 <= val) {
				strbuf_addch(out, val);
				q += 3;
				len -= 3;
				continue;
			}
		}

		if (decode_plus && c == '+')
			strbuf_addch(out, ' ');
		else
			strbuf_addch(out, c);
		q++;
		len--;
	}
	*query = q;
	return strbuf_detach(out, NULL);
}