static int is_rfc3986_unreserved(char ch)
{
	return isalnum(ch) ||
		ch == '-' || ch == '_' || ch == '.' || ch == '~';
}