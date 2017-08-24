{
	if (archive_wstring_ensure(as, as->length + s + 1) == NULL)
		return (NULL);
	wmemmove(as->s + as->length, p, s);
	as->length += s;
	as->s[as->length] = 0;
	return (as);
}