char *do_mktemp(char *template)
{
	if (dry_run) return NULL;
	if (read_only) {errno = EROFS; return NULL;}
	return mktemp(template);
}