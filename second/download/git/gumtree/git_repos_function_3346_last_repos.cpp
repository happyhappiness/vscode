static void hdr_int(struct strbuf *hdr, const char *name, uintmax_t value)
{
	strbuf_addf(hdr, "%s: %" PRIuMAX "\r\n", name, value);
}