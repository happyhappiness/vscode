void prune_packed_objects(int opts)
{
	int i;
	const char *dir = get_object_directory();
	struct strbuf pathname = STRBUF_INIT;
	int top_len;

	strbuf_addstr(&pathname, dir);
	if (opts & PRUNE_PACKED_VERBOSE)
		progress = start_progress_delay(_("Removing duplicate objects"),
			256, 95, 2);

	if (pathname.len && pathname.buf[pathname.len - 1] != '/')
		strbuf_addch(&pathname, '/');

	top_len = pathname.len;
	for (i = 0; i < 256; i++) {
		DIR *d;

		display_progress(progress, i + 1);
		strbuf_setlen(&pathname, top_len);
		strbuf_addf(&pathname, "%02x/", i);
		d = opendir(pathname.buf);
		if (!d)
			continue;
		prune_dir(i, d, &pathname, opts);
		closedir(d);
		strbuf_setlen(&pathname, top_len + 2);
		rmdir(pathname.buf);
	}
	stop_progress(&progress);
}