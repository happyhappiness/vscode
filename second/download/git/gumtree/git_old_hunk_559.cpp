	if (is_bool)
		strbuf_addstr(&buf, value ? "true" : "false");
	else
		quote_c_style(value, &buf, NULL, 0);
	strbuf_addch(&buf, '\n');

	sendline(data, &buf);
	if (recvline(data, &buf))
		exit(128);

	if (!strcmp(buf.buf, "ok"))
		ret = 0;
	else if (starts_with(buf.buf, "error")) {
		ret = -1;
	} else if (!strcmp(buf.buf, "unsupported"))
		ret = 1;
	else {
		warning("%s unexpectedly said: '%s'", data->name, buf.buf);
		ret = 1;
	}
	strbuf_release(&buf);
	return ret;
}

static void standard_options(struct transport *t)
{
