static void parse_cmd_delete(const char *next)
{
	struct strbuf ref = STRBUF_INIT;
	struct strbuf oldvalue = STRBUF_INIT;
	struct ref_update *update;

	update = update_alloc();

	if ((next = parse_first_arg(next, &ref)) != NULL && ref.buf[0])
		update_store_ref_name(update, ref.buf);
	else
		die("delete line missing <ref>");

	if ((next = parse_next_arg(next, &oldvalue)) != NULL)
		update_store_old_sha1(update, oldvalue.buf);
	else if(!line_termination)
		die("delete %s missing [<oldvalue>] NUL", ref.buf);
	if (update->have_old && is_null_sha1(update->old_sha1))
		die("delete %s given zero old value", ref.buf);

	if (next && *next)
		die("delete %s has extra input: %s", ref.buf, next);
}