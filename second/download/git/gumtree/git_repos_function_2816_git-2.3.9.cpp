static const char *get_canon_hostname(void)
{
	lookup_hostname();
	return canon_hostname;
}