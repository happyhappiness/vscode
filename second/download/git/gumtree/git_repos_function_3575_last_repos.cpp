static int is_cmarker(char *buf, int marker_char, int marker_size)
{
	int want_sp;

	/*
	 * The beginning of our version and the end of their version
	 * always are labeled like "<<<<< ours" or ">>>>> theirs",
	 * hence we set want_sp for them.  Note that the version from
	 * the common ancestor in diff3-style output is not always
	 * labelled (e.g. "||||| common" is often seen but "|||||"
	 * alone is also valid), so we do not set want_sp.
	 */
	want_sp = (marker_char == '<') || (marker_char == '>');

	while (marker_size--)
		if (*buf++ != marker_char)
			return 0;
	if (want_sp && *buf != ' ')
		return 0;
	return isspace(*buf);
}