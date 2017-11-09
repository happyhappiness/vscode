static int hunk_comment_line(const char *bol)
{
	int ch;

	if (!bol)
		return 0;
	ch = *bol & 0xff;
	return (isalpha(ch) || ch == '_' || ch == '$');
}