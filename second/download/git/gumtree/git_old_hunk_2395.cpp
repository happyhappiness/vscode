			 * preimage, more "+" lines may come after it.
			 */
			return;
		}
		diff_words_flush(ecbdata);
		if (ecbdata->diff_words->type == DIFF_WORDS_PORCELAIN) {
			emit_line(ecbdata->opt, plain, reset, line, len);
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
			emit_line(ecbdata->opt, plain, reset, line, len);
		}
		return;
	}

	if (line[0] != '+') {
		const char *color =
			diff_get_color(ecbdata->color_diff,
				       line[0] == '-' ? DIFF_FILE_OLD : DIFF_PLAIN);
		ecbdata->lno_in_preimage++;
		if (line[0] == ' ')
			ecbdata->lno_in_postimage++;
		emit_line(ecbdata->opt, color, reset, line, len);
	} else {
		ecbdata->lno_in_postimage++;
