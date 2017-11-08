static void show_name(struct strbuf *sb, const struct name_decoration *decoration)
{
	if (decoration_flags == DECORATE_SHORT_REFS)
		strbuf_addstr(sb, prettify_refname(decoration->name));
	else
		strbuf_addstr(sb, decoration->name);
}