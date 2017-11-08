static void emit_add_line(const char *reset,
			  struct emit_callback *ecbdata,
			  const char *line, int len)
{
	const char *ws = diff_get_color(ecbdata->color_diff, DIFF_WHITESPACE);
	const char *set = diff_get_color(ecbdata->color_diff, DIFF_FILE_NEW);

	if (!*ws)
		emit_line_0(ecbdata->opt, set, reset, '+', line, len);
	else if (new_blank_line_at_eof(ecbdata, line, len))
		/* Blank line at EOF - paint '+' as well */
		emit_line_0(ecbdata->opt, ws, reset, '+', line, len);
	else {
		/* Emit just the prefix, then the rest. */
		emit_line_0(ecbdata->opt, set, reset, '+', "", 0);
		ws_check_emit(line, len, ecbdata->ws_rule,
			      ecbdata->opt->file, set, reset, ws);
	}
}