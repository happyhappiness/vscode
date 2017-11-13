static void parse_cmd_create(const char *next)
{
	struct strbuf ref = STRBUF_INIT;
	struct strbuf newvalue = STRBUF_INIT;
	struct ref_update *update;

	update = update_alloc();
	update->have_old = 1;

	if ((next = parse_first_arg(next, &ref)) != NULL && ref.buf[0])
		update_store_ref_name(update, ref.buf);
	else
		die("create line missing <ref>");

	if ((next = parse_next_arg(next, &newvalue)) != NULL)
		update_store_new_sha1(update, newvalue.buf);
	else
		die("create %s missing <newvalue>", ref.buf);
	if (is_null_sha1(update->new_sha1))
		die("create %s given zero new value", ref.buf);

	if (next && *next)
		die("create %s has extra input: %s", ref.buf, next);
}