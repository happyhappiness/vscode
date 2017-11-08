int iconvbufs(iconv_t ic, xbuf *in, xbuf *out, int flags)
{
	ICONV_CONST char *ibuf;
	size_t icnt, ocnt;
	char *obuf;

	if (!out->size && flags & ICB_EXPAND_OUT)
		alloc_xbuf(out, 1024);

	if (!in->pos)
		iconv(ic, NULL, 0, NULL, 0);

	ibuf = in->buf + in->pos;
	icnt = in->len;

	obuf = out->buf + (out->pos + out->len);
	ocnt = out->size - (out->pos + out->len) - 1;

	while (icnt) {
		while (iconv(ic, &ibuf, &icnt, &obuf, &ocnt) == (size_t)-1) {
			if (errno == EINTR)
				continue;
			if (errno == EINVAL) {
				if (!(flags & ICB_INCLUDE_INCOMPLETE))
					goto finish;
			} else if (errno == EILSEQ) {
				if (!(flags & ICB_INCLUDE_BAD))
					goto finish;
			} else {
				size_t opos = obuf - out->buf;
				if (!(flags & ICB_EXPAND_OUT)) {
					errno = E2BIG;
					goto finish;
				}
				realloc_xbuf(out, out->size + 1024);
				obuf = out->buf + opos;
				ocnt += 1024;
				continue;
			}
			*obuf++ = *ibuf++;
			ocnt--, icnt--;
		}
	}

	errno = 0;

  finish:
	in->len = icnt;
	in->pos = ibuf - in->buf;
	out->len = obuf - out->buf - out->pos;

	return errno ? -1 : 0;
}