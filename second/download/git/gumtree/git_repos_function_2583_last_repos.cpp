static int is_inbody_header(const struct mailinfo *mi,
			    const struct strbuf *line)
{
	int i;
	for (i = 0; header[i]; i++)
		if (!mi->s_hdr_data[i] && cmp_header(line, header[i]))
			return 1;
	return 0;
}