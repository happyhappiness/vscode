static inline int invalid_value_char(const char ch)
{
	if (isalnum(ch) || strchr(",-_", ch))
		return 0;
	return -1;
}