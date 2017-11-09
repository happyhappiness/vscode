static const char *gpg_sign_opt_quoted(struct replay_opts *opts)
{
	static struct strbuf buf = STRBUF_INIT;

	strbuf_reset(&buf);
	if (opts->gpg_sign)
		sq_quotef(&buf, "-S%s", opts->gpg_sign);
	return buf.buf;
}