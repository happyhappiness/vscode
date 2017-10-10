	for (i = start; lines[i] && i < end; i++)
		fprintf(outfile, "%s", lines[i]->buf);
}

static int process_input_file(FILE *outfile,
			      struct strbuf **lines,
			      struct list_head *head)
{
	int count = 0;
	int patch_start, trailer_start, trailer_end, i;
	struct strbuf tok = STRBUF_INIT;
	struct strbuf val = STRBUF_INIT;
	struct trailer_item *last = NULL;

	/* Get the line count */
	while (lines[count])
		count++;

	patch_start = find_patch_start(lines, count);
