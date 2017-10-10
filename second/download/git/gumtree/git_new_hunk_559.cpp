	if (is_bool)
		strbuf_addstr(&buf, value ? "true" : "false");
	else
		quote_c_style(value, &buf, NULL, 0);
	strbuf_addch(&buf, '\n');

	ret = strbuf_set_helper_option(data, &buf);
	strbuf_release(&buf);
	return ret;
}

static void standard_options(struct transport *t)
{
