	for ( ; p; p = p->next) {
		printf(" %s", find_unique_abbrev(p->item->object.sha1, abbrev));
	}
}

/*
 * The caller makes sure there is no funny color before calling.
 * format_decorations_extended makes sure the same after return.
 */
void format_decorations_extended(struct strbuf *sb,
			const struct commit *commit,
			int use_color,
			const char *prefix,
			const char *separator,
			const char *suffix)
{
	const struct name_decoration *decoration;
	const char *color_commit =
		diff_get_color(use_color, DIFF_COMMIT);
	const char *color_reset =
		decorate_get_color(use_color, DECORATION_NONE);

	decoration = get_name_decoration(&commit->object);
	if (!decoration)
		return;
	while (decoration) {
		strbuf_addstr(sb, color_commit);
		strbuf_addstr(sb, prefix);
		strbuf_addstr(sb, color_reset);
		strbuf_addstr(sb, decorate_get_color(use_color, decoration->type));
		if (decoration->type == DECORATION_REF_TAG)
			strbuf_addstr(sb, "tag: ");
		strbuf_addstr(sb, decoration->name);
		strbuf_addstr(sb, color_reset);
		prefix = separator;
		decoration = decoration->next;
	}
	strbuf_addstr(sb, color_commit);
	strbuf_addstr(sb, suffix);
	strbuf_addstr(sb, color_reset);
}
