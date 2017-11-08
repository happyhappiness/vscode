static void get_sane_name(struct strbuf *out, struct strbuf *name, struct strbuf *email)
{
	struct strbuf *src = name;
	if (name->len < 3 || 60 < name->len || strchr(name->buf, '@') ||
		strchr(name->buf, '<') || strchr(name->buf, '>'))
		src = email;
	else if (name == out)
		return;
	strbuf_reset(out);
	strbuf_addbuf(out, src);
}