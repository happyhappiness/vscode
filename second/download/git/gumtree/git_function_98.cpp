static void parse_cmd_verify(const char *next)
{
	struct strbuf ref = STRBUF_INIT;
	struct strbuf value = STRBUF_INIT;
	struct ref_update *update;

	update = update_alloc();

	if ((next = parse_first_arg(next, &ref)) != NULL && ref.buf[0])
		update_store_ref_name(update, ref.buf);
	else
		die("verify line missing <ref>");

	if ((next = parse_next_arg(next, &value)) != NULL) {
		update_store_old_sha1(update, value.buf);
		update_store_new_sha1(update, value.buf);
	} else if(!line_termination)
		die("verify %s missing [<oldvalue>] NUL", ref.buf);

	if (next && *next)
		die("verify %s has extra input: %s", ref.buf, next);
}