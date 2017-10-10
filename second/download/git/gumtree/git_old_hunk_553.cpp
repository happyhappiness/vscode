
	if (!has_blank_line_before(lines, trailer_start - 1))
		fprintf(outfile, "\n");

	/* Parse trailer lines */
	for (i = trailer_start; i < trailer_end; i++) {
		if (lines[i]->buf[0] != comment_line_char) {
			struct trailer_item *new = create_trailer_item(lines[i]->buf);
			add_trailer_item(in_tok_first, in_tok_last, new);
		}
	}

	return trailer_end;
}

static void free_all(struct trailer_item **first)
{
	while (*first) {
		struct trailer_item *item = remove_first(first);
		free_trailer_item(item);
	}
}

static struct tempfile trailers_tempfile;

static FILE *create_in_place_tempfile(const char *file)
