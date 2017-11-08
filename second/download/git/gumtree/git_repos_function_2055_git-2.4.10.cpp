void sq_quote_argv(struct strbuf *dst, const char** argv, size_t maxlen)
{
	int i;

	/* Copy into destination buffer. */
	strbuf_grow(dst, 255);
	for (i = 0; argv[i]; ++i) {
		strbuf_addch(dst, ' ');
		sq_quote_buf(dst, argv[i]);
		if (maxlen && dst->len > maxlen)
			die("Too many or long arguments");
	}
}