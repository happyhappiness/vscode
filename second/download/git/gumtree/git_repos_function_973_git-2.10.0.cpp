size_t display_mode_esc_sequence_len(const char *s)
{
	const char *p = s;
	if (*p++ != '\033')
		return 0;
	if (*p++ != '[')
		return 0;
	while (isdigit(*p) || *p == ';')
		p++;
	if (*p++ != 'm')
		return 0;
	return p - s;
}