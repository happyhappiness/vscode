
static int process_input_file(struct strbuf **lines,
			      struct trailer_item **in_tok_first,
			      struct trailer_item **in_tok_last)
{
	int count = 0;
	int patch_start, trailer_start, i;

	/* Get the line count */
	while (lines[count])
		count++;

	patch_start = find_patch_start(lines, count);
	trailer_start = find_trailer_start(lines, patch_start);

	/* Print lines before the trailers as is */
	print_lines(lines, 0, trailer_start);

	if (!has_blank_line_before(lines, trailer_start - 1))
		printf("\n");

	/* Parse trailer lines */
	for (i = trailer_start; i < patch_start; i++) {
		if (lines[i]->buf[0] != comment_line_char) {
			struct trailer_item *new = create_trailer_item(lines[i]->buf);
			add_trailer_item(in_tok_first, in_tok_last, new);
		}
	}

	return patch_start;
}

static void free_all(struct trailer_item **first)
{
	while (*first) {
		struct trailer_item *item = remove_first(first);
