static char *credential_ask_one(const char *what, struct credential *c,
				int flags)
{
	struct strbuf desc = STRBUF_INIT;
	struct strbuf prompt = STRBUF_INIT;
	char *r;

	credential_describe(c, &desc);
	if (desc.len)
		strbuf_addf(&prompt, "%s for '%s': ", what, desc.buf);
	else
		strbuf_addf(&prompt, "%s: ", what);

	r = git_prompt(prompt.buf, flags);

	strbuf_release(&desc);
	strbuf_release(&prompt);
	return xstrdup(r);
}