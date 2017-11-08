static void hdr_date(const char *name, unsigned long when)
{
	const char *value = show_date(when, 0, DATE_MODE(RFC2822));
	hdr_str(name, value);
}