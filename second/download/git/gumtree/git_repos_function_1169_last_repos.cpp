int skip_utf8_bom(char **text, size_t len)
{
	if (len < strlen(utf8_bom) ||
	    memcmp(*text, utf8_bom, strlen(utf8_bom)))
		return 0;
	*text += strlen(utf8_bom);
	return 1;
}