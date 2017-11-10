static const char *get_super_prefix_or_empty(void)
{
	const char *s = get_super_prefix();
	if (!s)
		s = "";
	return s;
}