int gettext_width(const char *s)
{
	static int is_utf8 = -1;
	if (is_utf8 == -1)
		is_utf8 = !strcmp(charset, "UTF-8");

	return is_utf8 ? utf8_strwidth(s) : strlen(s);
}