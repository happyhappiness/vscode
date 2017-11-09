void strbuf_humanise_bytes(struct strbuf *buf, off_t bytes)
{
	if (bytes > 1 << 30) {
		strbuf_addf(buf, "%u.%2.2u GiB",
			    (int)(bytes >> 30),
			    (int)(bytes & ((1 << 30) - 1)) / 10737419);
	} else if (bytes > 1 << 20) {
		int x = bytes + 5243;  /* for rounding */
		strbuf_addf(buf, "%u.%2.2u MiB",
			    x >> 20, ((x & ((1 << 20) - 1)) * 100) >> 20);
	} else if (bytes > 1 << 10) {
		int x = bytes + 5;  /* for rounding */
		strbuf_addf(buf, "%u.%2.2u KiB",
			    x >> 10, ((x & ((1 << 10) - 1)) * 100) >> 10);
	} else {
		strbuf_addf(buf, "%u bytes", (int)bytes);
	}
}