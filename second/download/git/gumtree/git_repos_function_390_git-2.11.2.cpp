static int proto_is_http(const char *s)
{
	if (!s)
		return 0;
	return !strcmp(s, "https") || !strcmp(s, "http");
}