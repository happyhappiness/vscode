static void pp_handle_indent(struct pretty_print_context *pp,
			     struct strbuf *sb, int indent,
			     const char *line, int linelen)
{
	strbuf_addchars(sb, ' ', indent);
	if (pp->expand_tabs_in_log)
		strbuf_add_tabexpand(sb, pp->expand_tabs_in_log, line, linelen);
	else
		strbuf_add(sb, line, linelen);
}