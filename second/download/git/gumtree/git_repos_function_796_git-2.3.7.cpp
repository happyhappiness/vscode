static int grab_1st_switch(unsigned char *osha1, unsigned char *nsha1,
			   const char *email, unsigned long timestamp, int tz,
			   const char *message, void *cb_data)
{
	struct grab_1st_switch_cbdata *cb = cb_data;
	const char *target = NULL, *end;

	if (!starts_with(message, "checkout: moving from "))
		return 0;
	message += strlen("checkout: moving from ");
	target = strstr(message, " to ");
	if (!target)
		return 0;
	target += strlen(" to ");
	strbuf_reset(&cb->buf);
	hashcpy(cb->nsha1, nsha1);
	for (end = target; *end && *end != '\n'; end++)
		;
	strbuf_add(&cb->buf, target, end - target);
	return 1;
}