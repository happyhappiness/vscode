static const char *get_canon_hostname(struct hostinfo *hi)
{
	lookup_hostname(hi);
	return hi->canon_hostname.buf;
}