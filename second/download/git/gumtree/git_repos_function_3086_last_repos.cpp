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