static int is_cmarker(char *buf, int marker_char, int marker_size, int want_sp)
{
	while (marker_size--)
		if (*buf++ != marker_char)
			return 0;
	if (want_sp && *buf != ' ')
		return 0;
	return isspace(*buf);
}