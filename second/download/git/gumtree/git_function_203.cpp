static void fn_out_consume(void *priv, char *line, unsigned long len)
{
	struct emit_callback *ecbdata = priv;
	const char *meta = diff_get_color(ecbdata->color_diff, DIFF_METAINFO);
	const char *context = diff_get_color(ecbdata->color_diff, DIFF_CONTEXT);
	const char *reset = diff_get_color(ecbdata->color_diff, DIFF_RESET);
	struct diff_options *o = ecbdata->opt;
	const char *line_prefix = diff_line_prefix(o);

	if (ecbdata->header) {
		fprintf(ecbdata->opt->file, "%s", ecbdata->header->buf);
		strbuf_reset(ecbdata->header);
		ecbdata->header = NULL;
	}
	*(ecbdata->found_changesp) = 1;

	if (ecbdata->label_path[0]) {
		const char *name_a_tab, *name_b_tab;

		name_a_tab = strchr(ecbdata->label_path[0], ' ') ? "\t" : "";
		name_b_tab = strchr(ecbdata->label_path[1], ' ') ? "\t" : "";

		fprintf(ecbdata->opt->file, "%s%s--- %s%s%s\n",
			line_prefix, meta, ecbdata->label_path[0], reset, name_a_tab);
		fprintf(ecbdata->opt->file, "%s%s+++ %s%s%s\n",
			line_prefix, meta, ecbdata->label_path[1], reset, name_b_tab);
		ecbdata->label_path[0] = ecbdata->label_path[1] = NULL;
	}

	if (diff_suppress_blank_empty
	    && len == 2 && line[0] == ' ' && line[1] == '\n') {
		line[0] = '\n';
		len = 1;
	}

	if (line[0] == '@') {
		if (ecbdata->diff_words)
			diff_words_flush(ecbdata);
		len = sane_truncate_line(ecbdata, line, len);
		find_lno(line, ecbdata);
		emit_hunk_header(ecbdata, line, len);
		if (line[len-1] != '\n')
			putc('\n', ecbdata->opt->file);
		return;
	}

	if (len < 1) {
		emit_line(ecbdata->opt, reset, reset, line, len);
		if (ecbdata->diff_words
		    && ecbdata->diff_words->type == DIFF_WORDS_PORCELAIN)
			fputs("~\n", ecbdata->opt->file);
		return;
	}

	if (ecbdata->diff_words) {
		if (line[0] == '-') {
			diff_words_append(line, len,
					  &ecbdata->diff_words->minus);
			return;
		} else if (line[0] == '+') {
			diff_words_append(line, len,
					  &ecbdata->diff_words->plus);
			return;
		} else if (starts_with(line, "\\ ")) {
			/*
			 * Eat the "no newline at eof" marker as if we
			 * saw a "+" or "-" line with nothing on it,
			 * and return without diff_words_flush() to
			 * defer processing. If this is the end of
			 * preimage, more "+" lines may come after it.
			 */
			return;
		}
		diff_words_flush(ecbdata);
		if (ecbdata->diff_words->type == DIFF_WORDS_PORCELAIN) {
			emit_line(ecbdata->opt, context, reset, line, len);
			fputs("~\n", ecbdata->opt->file);
		} else {
			/*
			 * Skip the prefix character, if any.  With
			 * diff_suppress_blank_empty, there may be
			 * none.
			 */
			if (line[0] != '\n') {
			      line++;
			      len--;
			}
			emit_line(ecbdata->opt, context, reset, line, len);
		}
		return;
	}

	switch (line[0]) {
	case '+':
		ecbdata->lno_in_postimage++;
		emit_add_line(reset, ecbdata, line + 1, len - 1);
		break;
	case '-':
		ecbdata->lno_in_preimage++;
		emit_del_line(reset, ecbdata, line + 1, len - 1);
		break;
	case ' ':
		ecbdata->lno_in_postimage++;
		ecbdata->lno_in_preimage++;
		emit_context_line(reset, ecbdata, line + 1, len - 1);
		break;
	default:
		/* incomplete line at the end */
		ecbdata->lno_in_preimage++;
		emit_line(ecbdata->opt,
			  diff_get_color(ecbdata->color_diff, DIFF_CONTEXT),
			  reset, line, len);
		break;
	}
}