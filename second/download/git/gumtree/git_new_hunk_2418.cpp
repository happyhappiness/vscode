	memset(&xecfg, 0, sizeof(xecfg));
	diff_words_fill(&diff_words->minus, &minus, diff_words->word_regex);
	diff_words_fill(&diff_words->plus, &plus, diff_words->word_regex);
	xpp.flags = 0;
	/* as only the hunk header will be parsed, we need a 0-context */
	xecfg.ctxlen = 0;
	if (xdi_diff_outf(&minus, &plus, fn_out_diff_words_aux, diff_words,
			  &xpp, &xecfg))
		die("unable to generate word diff");
	free(minus.ptr);
	free(plus.ptr);
	if (diff_words->current_plus != diff_words->plus.text.ptr +
			diff_words->plus.text.size) {
		if (color_words_output_graph_prefix(diff_words))
			fputs(line_prefix, diff_words->opt->file);
