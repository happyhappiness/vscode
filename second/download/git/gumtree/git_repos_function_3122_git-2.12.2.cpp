static void hdr_str(struct strbuf *hdr, const char *name, const char *value)
{
	strbuf_addf(hdr, "%s: %s\r\n", name, value);
}