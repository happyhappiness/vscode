static int do_sign_commit(struct strbuf *buf, const char *keyid)
{
	struct strbuf sig = STRBUF_INIT;
	int inspos, copypos;

	/* find the end of the header */
	inspos = strstr(buf->buf, "\n\n") - buf->buf + 1;

	if (!keyid || !*keyid)
		keyid = get_signing_key();
	if (sign_buffer(buf, &sig, keyid)) {
		strbuf_release(&sig);
		return -1;
	}

	for (copypos = 0; sig.buf[copypos]; ) {
		const char *bol = sig.buf + copypos;
		const char *eol = strchrnul(bol, '\n');
		int len = (eol - bol) + !!*eol;

		if (!copypos) {
			strbuf_insert(buf, inspos, gpg_sig_header, gpg_sig_header_len);
			inspos += gpg_sig_header_len;
		}
		strbuf_insert(buf, inspos++, " ", 1);
		strbuf_insert(buf, inspos, bol, len);
		inspos += len;
		copypos += len;
	}
	strbuf_release(&sig);
	return 0;
}