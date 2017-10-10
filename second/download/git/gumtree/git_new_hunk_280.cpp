		if (ecbdata->diff_words)
			diff_words_flush(ecbdata);
		len = sane_truncate_line(ecbdata, line, len);
		find_lno(line, ecbdata);
		emit_hunk_header(ecbdata, line, len);
		if (line[len-1] != '\n')
			putc('\n', o->file);
		return;
	}

	if (ecbdata->diff_words) {
		if (line[0] == '-') {
			diff_words_append(line, len,
