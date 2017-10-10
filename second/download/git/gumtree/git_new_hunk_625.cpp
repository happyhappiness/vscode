}

static void flush_inbody_header_accum(struct mailinfo *mi)
{
	if (!mi->inbody_header_accum.len)
		return;
	if (!check_header(mi, &mi->inbody_header_accum, mi->s_hdr_data, 0))
		die("BUG: inbody_header_accum, if not empty, must always contain a valid in-body header");
	strbuf_reset(&mi->inbody_header_accum);
}

static int check_inbody_header(struct mailinfo *mi, const struct strbuf *line)
{
	if (mi->inbody_header_accum.len &&
