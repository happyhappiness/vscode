static void strbuf_write_column(struct strbuf *sb, const struct column *c,
				char col_char)
{
	if (c->color < column_colors_max)
		strbuf_addstr(sb, column_get_color_code(c->color));
	strbuf_addch(sb, col_char);
	if (c->color < column_colors_max)
		strbuf_addstr(sb, column_get_color_code(column_colors_max));
}