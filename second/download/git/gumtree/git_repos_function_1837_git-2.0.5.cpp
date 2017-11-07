int ends_with(const char *str, const char *suffix)
{
	int len = strlen(str), suflen = strlen(suffix);
	if (len < suflen)
		return 0;
	else
		return !strcmp(str + len - suflen, suffix);
}