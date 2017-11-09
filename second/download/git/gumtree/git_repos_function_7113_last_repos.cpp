static int match_part_with_last(LPCWSTR *ptarget, LPCWSTR want, LPCWSTR delim, int last)
{
	LPCWSTR delim_pos, start = *ptarget;
	int len;

	/* find start of delimiter (or end-of-string if delim is empty) */
	if (*delim)
		delim_pos = last ? wcsstr_last(start, delim) : wcsstr(start, delim);
	else
		delim_pos = start + wcslen(start);

	/*
	 * match text up to delimiter, or end of string (e.g. the '/' after
	 * host is optional if not followed by a path)
	 */
	if (delim_pos)
		len = delim_pos - start;
	else
		len = wcslen(start);

	/* update ptarget if we either found a delimiter or need a match */
	if (delim_pos || want)
		*ptarget = delim_pos ? delim_pos + wcslen(delim) : start + len;

	return !want || (!wcsncmp(want, start, len) && !want[len]);
}