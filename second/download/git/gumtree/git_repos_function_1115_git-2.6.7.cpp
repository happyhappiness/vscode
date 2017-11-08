static void emit_line_checked(const char *reset,
			      struct emit_callback *ecbdata,
			      const char *line, int len,
			      enum color_diff color,
			      unsigned ws_error_highlight,
			      char sign)
{
	const char *set = diff_get_color(ecbdata->color_diff, color);
	const char *ws = NULL;

	if (ecbdata->opt->ws_error_highlight & ws_error_highlight) {
		ws = diff_get_color(ecbdata->color_diff, DIFF_WHITESPACE);
		if (!*ws)
			ws = NULL;
	}

	if (!ws)
		emit_line_0(ecbdata->opt, set, reset, sign, line, len);
	else if (sign == '+' && new_blank_line_at_eof(ecbdata, line, len))
		/* Blank line at EOF - paint '+' as well */
		emit_line_0(ecbdata->opt, ws, reset, sign, line, len);
	else {
		/* Emit just the prefix, then the rest. */
		emit_line_0(ecbdata->opt, set, reset, sign, "", 0);
		ws_check_emit(line, len, ecbdata->ws_rule,
			      ecbdata->opt->file, set, reset, ws);
	}
}