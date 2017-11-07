static void handle_info(void)
{
	struct strbuf *hdr;
	int i;

	for (i = 0; header[i]; i++) {
		/* only print inbody headers if we output a patch file */
		if (patch_lines && s_hdr_data[i])
			hdr = s_hdr_data[i];
		else if (p_hdr_data[i])
			hdr = p_hdr_data[i];
		else
			continue;

		if (!strcmp(header[i], "Subject")) {
			if (!keep_subject) {
				cleanup_subject(hdr);
				cleanup_space(hdr);
			}
			output_header_lines(fout, "Subject", hdr);
		} else if (!strcmp(header[i], "From")) {
			cleanup_space(hdr);
			handle_from(hdr);
			fprintf(fout, "Author: %s\n", name.buf);
			fprintf(fout, "Email: %s\n", email.buf);
		} else {
			cleanup_space(hdr);
			fprintf(fout, "%s: %s\n", header[i], hdr->buf);
		}
	}
	fprintf(fout, "\n");
}