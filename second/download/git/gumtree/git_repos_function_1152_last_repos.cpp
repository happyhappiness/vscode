int utf8_width(const char **start, size_t *remainder_p)
{
	ucs_char_t ch = pick_one_utf8_char(start, remainder_p);
	if (!*start)
		return 0;
	return git_wcwidth(ch);
}