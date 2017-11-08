static LPCWSTR wcsstr_last(LPCWSTR str, LPCWSTR find)
{
	LPCWSTR res = NULL, pos;
	for (pos = wcsstr(str, find); pos; pos = wcsstr(pos + 1, find))
		res = pos;
	return res;
}