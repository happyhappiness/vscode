}

void process_trailers(const char *file, int in_place, int trim_empty, struct string_list *trailers)
{
	LIST_HEAD(head);
	LIST_HEAD(arg_head);
	struct strbuf sb = STRBUF_INIT;
	int trailer_end;
	FILE *outfile = stdout;

	ensure_configured();

	read_input_file(&sb, file);

	if (in_place)
		outfile = create_in_place_tempfile(file);

	/* Print the lines before the trailers */
	trailer_end = process_input_file(outfile, sb.buf, &head);

	process_command_line_args(&arg_head, trailers);

	process_trailers_lists(&head, &arg_head);

	print_all(outfile, &head, trim_empty);

	free_all(&head);

	/* Print the lines after the trailers as is */
	fwrite(sb.buf + trailer_end, 1, sb.len - trailer_end, outfile);

	if (in_place)
		if (rename_tempfile(&trailers_tempfile, file))
			die_errno(_("could not rename temporary file to %s"), file);

	strbuf_release(&sb);
}

void trailer_info_get(struct trailer_info *info, const char *str)
{
	int patch_start, trailer_end, trailer_start;
	struct strbuf **trailer_lines, **ptr;
	char **trailer_strings = NULL;
	size_t nr = 0, alloc = 0;
	char **last = NULL;

	ensure_configured();

	patch_start = find_patch_start(str);
	trailer_end = find_trailer_end(str, patch_start);
	trailer_start = find_trailer_start(str, trailer_end);

	trailer_lines = strbuf_split_buf(str + trailer_start,
					 trailer_end - trailer_start,
					 '\n',
					 0);
	for (ptr = trailer_lines; *ptr; ptr++) {
		if (last && isspace((*ptr)->buf[0])) {
			struct strbuf sb = STRBUF_INIT;
			strbuf_attach(&sb, *last, strlen(*last), strlen(*last));
			strbuf_addbuf(&sb, *ptr);
			*last = strbuf_detach(&sb, NULL);
			continue;
		}
		ALLOC_GROW(trailer_strings, nr + 1, alloc);
		trailer_strings[nr] = strbuf_detach(*ptr, NULL);
		last = find_separator(trailer_strings[nr], separators) >= 1
			? &trailer_strings[nr]
			: NULL;
		nr++;
	}
	strbuf_list_free(trailer_lines);

	info->blank_line_before_trailer = ends_with_blank_line(str,
							       trailer_start);
	info->trailer_start = str + trailer_start;
	info->trailer_end = str + trailer_end;
	info->trailers = trailer_strings;
	info->trailer_nr = nr;
}

void trailer_info_release(struct trailer_info *info)
{
	int i;
	for (i = 0; i < info->trailer_nr; i++)
		free(info->trailers[i]);
	free(info->trailers);
}
