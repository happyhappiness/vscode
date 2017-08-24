{
	struct match *match;

	match = calloc(1, sizeof(*match));
	if (match == NULL)
		return (error_nomem(a));
	if (mbs)
		archive_mstring_copy_mbs(&(match->pattern), name);
	else
		archive_mstring_copy_wcs(&(match->pattern), name);
	match_list_add(list, match);
	a->setflag |= ID_IS_SET;
	return (ARCHIVE_OK);
}