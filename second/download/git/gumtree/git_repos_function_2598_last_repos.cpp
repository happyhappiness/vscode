static void handle_info(struct mailinfo *mi)
{
	struct strbuf *hdr;
	int i;

	for (i = 0; header[i]; i++) {
		/* only print inbody headers if we output a patch file */
		if (mi->patch_lines && mi->s_hdr_data[i])
			hdr = mi->s_hdr_data[i];
		else if (mi->p_hdr_data[i])
			hdr = mi->p_hdr_data[i];
		else
			continue;

		if (!strcmp(header[i], "Subject")) {
			if (!mi->keep_subject) {
				cleanup_subject(mi, hdr);
				cleanup_space(hdr);
			}
			output_header_lines(mi->output, "Subject", hdr);
		} else if (!strcmp(header[i], "From")) {
			cleanup_space(hdr);
			handle_from(mi, hdr);
			fprintf(mi->output, "Author: %s\n", mi->name.buf);
			fprintf(mi->output, "Email: %s\n", mi->email.buf);
		} else {
			cleanup_space(hdr);
			fprintf(mi->output, "%s: %s\n", header[i], hdr->buf);
		}
	}
	fprintf(mi->output, "\n");
}