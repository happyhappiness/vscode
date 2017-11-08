static void export_one(const char *var, const char *s, const char *e, int hack)
{
	struct strbuf buf = STRBUF_INIT;
	if (hack)
		strbuf_addch(&buf, hack);
	strbuf_addf(&buf, "%.*s", (int)(e - s), s);
	setenv(var, buf.buf, 1);
	strbuf_release(&buf);
}