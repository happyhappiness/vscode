static inline int bad_ref_char(int ch)
{
	if (((unsigned) ch) <= ' ' || ch == 0x7f ||
	    ch == '~' || ch == '^' || ch == ':' || ch == '\\')
		return 1;
	/* 2.13 Pattern Matching Notation */
	if (ch == '*' || ch == '?' || ch == '[') /* Unsupported */
		return 1;
	return 0;
}