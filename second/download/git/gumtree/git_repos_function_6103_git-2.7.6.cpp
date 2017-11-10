char *strdup(const char *s1)
{
	char *s2 = 0;
	if (s1) {
		size_t len = strlen(s1) + 1;
		s2 = malloc(len);
		memcpy(s2, s1, len);
	}
	return s2;
}