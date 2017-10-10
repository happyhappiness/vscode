 * terminating NUL.
 */
static int link_alt_odb_entry(const char *entry, const char *relative_base,
	int depth, const char *normalized_objdir)
{
	struct alternate_object_database *ent;
	struct strbuf pathbuf = STRBUF_INIT;

	if (!is_absolute_path(entry) && relative_base) {
		strbuf_addstr(&pathbuf, real_path(relative_base));
		strbuf_addch(&pathbuf, '/');
	}
	strbuf_addstr(&pathbuf, entry);

	if (strbuf_normalize_path(&pathbuf) < 0 && relative_base) {
		error("unable to normalize alternate object path: %s",
		      pathbuf.buf);
		strbuf_release(&pathbuf);
		return -1;
	}

	/*
	 * The trailing slash after the directory name is given by
	 * this function at the end. Remove duplicates.
	 */
	while (pathbuf.len && pathbuf.buf[pathbuf.len - 1] == '/')
		strbuf_setlen(&pathbuf, pathbuf.len - 1);

	if (!alt_odb_usable(&pathbuf, normalized_objdir)) {
		strbuf_release(&pathbuf);
		return -1;
	}

	ent = alloc_alt_odb(pathbuf.buf);

	/* add the alternate entry */
	*alt_odb_tail = ent;
	alt_odb_tail = &(ent->next);
	ent->next = NULL;

	/* recursively add alternates */
	read_info_alternates(pathbuf.buf, depth + 1);

	strbuf_release(&pathbuf);
	return 0;
}

static void link_alt_odb_entries(const char *alt, int len, int sep,
				 const char *relative_base, int depth)
{
