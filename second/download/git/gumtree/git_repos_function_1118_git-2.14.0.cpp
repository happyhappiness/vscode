static int grab_1st_switch(struct object_id *ooid, struct object_id *noid,
			   const char *email, timestamp_t timestamp, int tz,
			   const char *message, void *cb_data)
{
	struct grab_1st_switch_cbdata *cb = cb_data;
	const char *target = NULL, *end;

	if (!skip_prefix(message, "checkout: moving from ", &message))
		return 0;
	target = strstr(message, " to ");
	if (!target)
		return 0;
	target += strlen(" to ");
	strbuf_reset(&cb->buf);
	oidcpy(&cb->noid, noid);
	end = strchrnul(target, '\n');
	strbuf_add(&cb->buf, target, end - target);
	if (!strcmp(cb->buf.buf, "HEAD")) {
		/* HEAD is relative. Resolve it to the right reflog entry. */
		strbuf_reset(&cb->buf);
		strbuf_add_unique_abbrev(&cb->buf, noid->hash, DEFAULT_ABBREV);
	}
	return 1;
}