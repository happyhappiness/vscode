static void parse_cmd_update(const char *next)
{
	struct strbuf ref = STRBUF_INIT;
	struct strbuf newvalue = STRBUF_INIT;
	struct strbuf oldvalue = STRBUF_INIT;
	struct ref_update *update;

	update = update_alloc();

	if ((next = parse_first_arg(next, &ref)) != NULL && ref.buf[0])
		update_store_ref_name(update, ref.buf);
	else
		die("update line missing <ref>");

	if ((next = parse_next_arg(next, &newvalue)) != NULL)
		update_store_new_sha1(update, newvalue.buf);
	else
		die("update %s missing <newvalue>", ref.buf);

	if ((next = parse_next_arg(next, &oldvalue)) != NULL)
		update_store_old_sha1(update, oldvalue.buf);
	else if(!line_termination)
		die("update %s missing [<oldvalue>] NUL", ref.buf);

	if (next && *next)
		die("update %s has extra input: %s", ref.buf, next);
}