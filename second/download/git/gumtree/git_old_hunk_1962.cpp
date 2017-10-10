
static int is_a_merge(const struct commit *current_head)
{
	return !!(current_head->parents && current_head->parents->next);
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

static int sane_ident_split(struct ident_split *person)
{
	if (!person->name_begin || !person->name_end ||
	    person->name_begin == person->name_end)
		return 0; /* no human readable name */
	if (!person->mail_begin || !person->mail_end ||
	    person->mail_begin == person->mail_end)
		return 0; /* no usable mail */
	if (!person->date_begin || !person->date_end ||
	    !person->tz_begin || !person->tz_end)
		return 0;
	return 1;
}

static int parse_force_date(const char *in, struct strbuf *out)
{
	strbuf_addch(out, '@');

	if (parse_date(in, out) < 0) {
		int errors = 0;
