
static int is_a_merge(const struct commit *current_head)
{
	return !!(current_head->parents && current_head->parents->next);
}

static void assert_split_ident(struct ident_split *id, const struct strbuf *buf)
{
	if (split_ident_line(id, buf->buf, buf->len) || !id->date_begin)
		die("BUG: unable to parse our own ident: %s", buf->buf);
}

static void export_one(const char *var, const char *s, const char *e, int hack)
{
	struct strbuf buf = STRBUF_INIT;
	if (hack)
		strbuf_addch(&buf, hack);
	strbuf_addf(&buf, "%.*s", (int)(e - s), s);
	setenv(var, buf.buf, 1);
	strbuf_release(&buf);
}

static int parse_force_date(const char *in, struct strbuf *out)
{
	strbuf_addch(out, '@');

	if (parse_date(in, out) < 0) {
		int errors = 0;
