static void hdr_date(struct strbuf *hdr, const char *name, timestamp_t when)
{
	const char *value = show_date(when, 0, DATE_MODE(RFC2822));
	hdr_str(hdr, name, value);
}