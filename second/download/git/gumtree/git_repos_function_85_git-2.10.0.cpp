static int non_ascii(int ch)
{
	return !isascii(ch) || ch == '\033';
}