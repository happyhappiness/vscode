static void checkdiff_consume(void *priv, char *line, unsigned long len)
{
	struct checkdiff_t *data = priv;
	int marker_size = data->conflict_marker_size;
	const char *ws = diff_get_color(data->o->use_color, DIFF_WHITESPACE);
	const char *reset = diff_get_color(data->o->use_color, DIFF_RESET);
	const char *set = diff_get_color(data->o->use_color, DIFF_FILE_NEW);
	char *err;
	const char *line_prefix;

	assert(data->o);
	line_prefix = diff_line_prefix(data->o);

	if (line[0] == '+') {
		unsigned bad;
		data->lineno++;
		if (is_conflict_marker(line + 1, marker_size, len - 1)) {
			data->status |= 1;
			fprintf(data->o->file,
				"%s%s:%d: leftover conflict marker\n",
				line_prefix, data->filename, data->lineno);
		}
		bad = ws_check(line + 1, len - 1, data->ws_rule);
		if (!bad)
			return;
		data->status |= bad;
		err = whitespace_error_string(bad);
		fprintf(data->o->file, "%s%s:%d: %s.\n",
			line_prefix, data->filename, data->lineno, err);
		free(err);
		emit_line(data->o, set, reset, line, 1);
		ws_check_emit(line + 1, len - 1, data->ws_rule,
			      data->o->file, set, reset, ws);
	} else if (line[0] == ' ') {
		data->lineno++;
	} else if (line[0] == '@') {
		char *plus = strchr(line, '+');
		if (plus)
			data->lineno = strtol(plus, NULL, 10) - 1;
		else
			die("invalid diff");
	}
}