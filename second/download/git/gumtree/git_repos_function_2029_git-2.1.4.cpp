void format_decorations(struct strbuf *sb,
			const struct commit *commit,
			int use_color)
{
	const char *prefix;
	struct name_decoration *decoration;
	const char *color_commit =
		diff_get_color(use_color, DIFF_COMMIT);
	const char *color_reset =
		decorate_get_color(use_color, DECORATION_NONE);

	decoration = lookup_decoration(&name_decoration, &commit->object);
	if (!decoration)
		return;
	prefix = " (";
	while (decoration) {
		strbuf_addstr(sb, color_commit);
		strbuf_addstr(sb, prefix);
		strbuf_addstr(sb, decorate_get_color(use_color, decoration->type));
		if (decoration->type == DECORATION_REF_TAG)
			strbuf_addstr(sb, "tag: ");
		strbuf_addstr(sb, decoration->name);
		strbuf_addstr(sb, color_reset);
		prefix = ", ";
		decoration = decoration->next;
	}
	strbuf_addstr(sb, color_commit);
	strbuf_addch(sb, ')');
	strbuf_addstr(sb, color_reset);
}