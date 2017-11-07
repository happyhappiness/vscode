static void packet_trace(const char *buf, unsigned int len, int write)
{
	int i;
	struct strbuf out;

	if (!trace_want(trace_key))
		return;

	/* +32 is just a guess for header + quoting */
	strbuf_init(&out, len+32);

	strbuf_addf(&out, "packet: %12s%c ",
		    packet_trace_prefix, write ? '>' : '<');

	if ((len >= 4 && starts_with(buf, "PACK")) ||
	    (len >= 5 && starts_with(buf+1, "PACK"))) {
		strbuf_addstr(&out, "PACK ...");
		unsetenv(trace_key);
	}
	else {
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
	}

	strbuf_addch(&out, '\n');
	trace_strbuf(trace_key, &out);
	strbuf_release(&out);
}