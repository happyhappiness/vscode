static int match_part_last(LPCWSTR *ptarget, LPCWSTR want, LPCWSTR delim)
{
	return match_part_with_last(ptarget, want, delim, 1);
}