static int match_word(const char *word, int len, const char *match)
{
	return !strncasecmp(word, match, len) && !match[len];
}