static int packet_trace_pack(const char *buf, unsigned int len, int sideband)
{
	if (!sideband) {
		trace_verbatim(&trace_pack, buf, len);
		return 1;
	} else if (len && *buf == '\1') {
		trace_verbatim(&trace_pack, buf + 1, len - 1);
		return 1;
	} else {
		/* it's another non-pack sideband */
		return 0;
	}
}