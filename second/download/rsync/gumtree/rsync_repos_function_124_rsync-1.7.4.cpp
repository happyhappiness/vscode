char *do_mktemp(char *template)
{
	if (dry_run) return NULL;
	return mktemp(template);
}