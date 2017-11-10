static int is_rfc822_special(char ch)
{
	switch (ch) {
	case '(':
	case ')':
	case '<':
	case '>':
	case '[':
	case ']':
	case ':':
	case ';':
	case '@':
	case ',':
	case '.':
	case '"':
	case '\\':
		return 1;
	default:
		return 0;
	}
}