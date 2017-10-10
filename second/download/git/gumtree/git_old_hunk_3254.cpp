	while (*first) {
		struct trailer_item *item = remove_first(first);
		free_trailer_item(item);
	}
}

void process_trailers(const char *file, int trim_empty, struct string_list *trailers)
{
	struct trailer_item *in_tok_first = NULL;
	struct trailer_item *in_tok_last = NULL;
	struct trailer_item *arg_tok_first;
	struct strbuf **lines;
	int trailer_end;

	/* Default config must be setup first */
	git_config(git_trailer_default_config, NULL);
	git_config(git_trailer_config, NULL);

	lines = read_input_file(file);

	/* Print the lines before the trailers */
	trailer_end = process_input_file(lines, &in_tok_first, &in_tok_last);

	arg_tok_first = process_command_line_args(trailers);

	process_trailers_lists(&in_tok_first, &in_tok_last, &arg_tok_first);

	print_all(in_tok_first, trim_empty);

	free_all(&in_tok_first);

	/* Print the lines after the trailers as is */
	print_lines(lines, trailer_end, INT_MAX);

	strbuf_list_free(lines);
}
