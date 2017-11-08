char *strdup(char *s)
{
	int len = strlen(s) + 1;
	char *ret = (char *)malloc(len);
	if (ret)
		memcpy(ret, s, len);
	return ret;
}