static int ident_in_untracked(const struct untracked_cache *uc)
{
	const char *end = uc->ident.buf + uc->ident.len;
	const char *p   = uc->ident.buf;

	for (p = uc->ident.buf; p < end; p += strlen(p) + 1)
		if (!strcmp(p, get_ident_string()))
			return 1;
	return 0;
}