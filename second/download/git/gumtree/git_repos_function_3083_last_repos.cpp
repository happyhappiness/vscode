static int process_input_file(FILE *outfile,
			      const char *str,
			      struct list_head *head)
{
	struct trailer_info info;
	struct strbuf tok = STRBUF_INIT;
	struct strbuf val = STRBUF_INIT;
	int i;

	trailer_info_get(&info, str);

	/* Print lines before the trailers as is */
	fwrite(str, 1, info.trailer_start - str, outfile);

	if (!info.blank_line_before_trailer)
		fprintf(outfile, "\n");

	for (i = 0; i < info.trailer_nr; i++) {
		int separator_pos;
		char *trailer = info.trailers[i];
		if (trailer[0] == comment_line_char)
			continue;
		separator_pos = find_separator(trailer, separators);
		if (separator_pos >= 1) {
			parse_trailer(&tok, &val, NULL, trailer,
				      separator_pos);
			add_trailer_item(head,
					 strbuf_detach(&tok, NULL),
					 strbuf_detach(&val, NULL));
		} else {
			strbuf_addstr(&val, trailer);
			strbuf_strip_suffix(&val, "\n");
			add_trailer_item(head,
					 NULL,
					 strbuf_detach(&val, NULL));
		}
	}

	trailer_info_release(&info);

	return info.trailer_end - str;
}