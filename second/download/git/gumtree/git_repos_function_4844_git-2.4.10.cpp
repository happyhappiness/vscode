static int decode_header_bq(struct strbuf *it)
{
	char *in, *ep, *cp;
	struct strbuf outbuf = STRBUF_INIT, *dec;
	struct strbuf charset_q = STRBUF_INIT, piecebuf = STRBUF_INIT;
	int rfc2047 = 0;

	in = it->buf;
	while (in - it->buf <= it->len && (ep = strstr(in, "=?")) != NULL) {
		int encoding;
		strbuf_reset(&charset_q);
		strbuf_reset(&piecebuf);
		rfc2047 = 1;

		if (in != ep) {
			/*
			 * We are about to process an encoded-word
			 * that begins at ep, but there is something
			 * before the encoded word.
			 */
			char *scan;
			for (scan = in; scan < ep; scan++)
				if (!isspace(*scan))
					break;

			if (scan != ep || in == it->buf) {
				/*
				 * We should not lose that "something",
				 * unless we have just processed an
				 * encoded-word, and there is only LWS
				 * before the one we are about to process.
				 */
				strbuf_add(&outbuf, in, ep - in);
			}
		}
		/* E.g.
		 * ep : "=?iso-2022-jp?B?GyR...?= foo"
		 * ep : "=?ISO-8859-1?Q?Foo=FCbar?= baz"
		 */
		ep += 2;

		if (ep - it->buf >= it->len || !(cp = strchr(ep, '?')))
			goto decode_header_bq_out;

		if (cp + 3 - it->buf > it->len)
			goto decode_header_bq_out;
		strbuf_add(&charset_q, ep, cp - ep);

		encoding = cp[1];
		if (!encoding || cp[2] != '?')
			goto decode_header_bq_out;
		ep = strstr(cp + 3, "?=");
		if (!ep)
			goto decode_header_bq_out;
		strbuf_add(&piecebuf, cp + 3, ep - cp - 3);
		switch (tolower(encoding)) {
		default:
			goto decode_header_bq_out;
		case 'b':
			dec = decode_b_segment(&piecebuf);
			break;
		case 'q':
			dec = decode_q_segment(&piecebuf, 1);
			break;
		}
		if (metainfo_charset)
			convert_to_utf8(dec, charset_q.buf);

		strbuf_addbuf(&outbuf, dec);
		strbuf_release(dec);
		free(dec);
		in = ep + 2;
	}
	strbuf_addstr(&outbuf, in);
	strbuf_reset(it);
	strbuf_addbuf(it, &outbuf);
decode_header_bq_out:
	strbuf_release(&outbuf);
	strbuf_release(&charset_q);
	strbuf_release(&piecebuf);
	return rfc2047;
}