static void throughput_string(struct strbuf *buf, off_t total,
			      unsigned int rate)
{
	strbuf_addstr(buf, ", ");
	strbuf_humanise_bytes(buf, total);
	strbuf_addstr(buf, " | ");
	strbuf_humanise_bytes(buf, rate * 1024);
	strbuf_addstr(buf, "/s");
}