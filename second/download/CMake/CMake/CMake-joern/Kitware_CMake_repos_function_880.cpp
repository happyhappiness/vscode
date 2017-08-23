int
archive_write_add_filter_by_name(struct archive *a, const char *name)
{
	int i;

	for (i = 0; names[i].name != NULL; i++) {
		if (strcmp(name, names[i].name) == 0)
			return ((names[i].setter)(a));
	}

	archive_set_error(a, EINVAL, "No such filter '%s'", name);
	a->state = ARCHIVE_STATE_FATAL;
	return (ARCHIVE_FATAL);
}