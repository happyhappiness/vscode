{
	struct match_file *f = (struct match_file *)(uintptr_t)n;
	const char *p;

	archive_mstring_get_mbs(NULL, &(f->pathname), &p);
	if (p == NULL)
		return (-1);
	return (strcmp(p, (const char *)key));
}