static void packet_trace(const char *buf, unsigned int len, int write)
{
	int i;
	struct strbuf out;
	static int in_pack, sideband;

	if (!trace_want(&trace_packet) && !trace_want(&trace_pack))
		return;

	if (in_pack) {
		if (packet_trace_pack(buf, len, sideband))
			return;
	} else if (starts_with(buf, "PACK") || starts_with(buf, "\1PACK")) {
		in_pack = 1;
		sideband = *buf == '\1';
		packet_trace_pack(buf, len, sideband);

		/*
		 * Make a note in the human-readable trace that the pack data
		 * started.
		 */
		buf = "PACK ...";
		len = strlen(buf);
	}

	if (!trace_want(&trace_packet))
		return;

	/* +32 is just a guess for header + quoting */
	strbuf_init(&out, len+32);

	strbuf_addf(&out, "packet: %12s%c ",
		    get_trace_prefix(), write ? '>' : '<');

	/* XXX we should really handle printable utf8 */
	for (i = 0; i < len; i++) {
		/* suppress newlines */
		if (buf[i] == '\n')
			continue;
		if (buf[i] >= 0x20 && buf[i] <= 0x7e)
			strbuf_addch(&out, buf[i]);
		else
			strbuf_addf(&out, "\\%o", buf[i]);
	}

	strbuf_addch(&out, '\n');
	trace_strbuf(&trace_packet, &out);
	strbuf_release(&out);
}