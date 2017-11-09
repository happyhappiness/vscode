static int check_inbody_header(struct mailinfo *mi, const struct strbuf *line)
{
	if (mi->inbody_header_accum.len &&
	    (line->buf[0] == ' ' || line->buf[0] == '\t')) {
		if (mi->use_scissors && is_scissors_line(line->buf)) {
			/*
			 * This is a scissors line; do not consider this line
			 * as a header continuation line.
			 */
			flush_inbody_header_accum(mi);
			return 0;
		}
		strbuf_strip_suffix(&mi->inbody_header_accum, "\n");
		strbuf_addbuf(&mi->inbody_header_accum, line);
		return 1;
	}

	flush_inbody_header_accum(mi);

	if (starts_with(line->buf, ">From") && isspace(line->buf[5]))
		return is_format_patch_separator(line->buf + 1, line->len - 1);
	if (starts_with(line->buf, "[PATCH]") && isspace(line->buf[7])) {
		int i;
		for (i = 0; header[i]; i++)
			if (!strcmp("Subject", header[i])) {
				handle_header(&mi->s_hdr_data[i], line);
				return 1;
			}
		return 0;
	}
	if (is_inbody_header(mi, line)) {
		strbuf_addbuf(&mi->inbody_header_accum, line);
		return 1;
	}
	return 0;
}