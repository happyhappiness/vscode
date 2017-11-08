static int supported_man_viewer(const char *name, size_t len)
{
	return (!strncasecmp("man", name, len) ||
		!strncasecmp("woman", name, len) ||
		!strncasecmp("konqueror", name, len));
}