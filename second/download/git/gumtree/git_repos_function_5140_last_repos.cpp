static void show_config_origin(struct strbuf *buf)
{
	const char term = end_null ? '\0' : '\t';

	strbuf_addstr(buf, current_config_origin_type());
	strbuf_addch(buf, ':');
	if (end_null)
		strbuf_addstr(buf, current_config_name());
	else
		quote_c_style(current_config_name(), buf, NULL, 0);
	strbuf_addch(buf, term);
}