	tree_push(t, base, t->full_path.s, 0, 0, 0, NULL);
	archive_wstring_free(&ws);
	t->stack->flags = needsFirstVisit;
	/*
	 * Debug flag for Direct IO(No buffering) or Async IO.
	 * Those dependant on environment variable switches
	 * will be removed until next release.
	 */
	{
		const char *e;
		if ((e = getenv("LIBARCHIVE_DIRECT_IO")) != NULL) {
			if (e[0] == '0')
				t->direct_io = 0;
			else
				t->direct_io = 1;
			fprintf(stderr, "LIBARCHIVE_DIRECT_IO=%s\n",
				(t->direct_io)?"Enabled":"Disabled");
		} else
			t->direct_io = DIRECT_IO;
		if ((e = getenv("LIBARCHIVE_ASYNC_IO")) != NULL) {
			if (e[0] == '0')
				t->async_io = 0;
			else
				t->async_io = 1;
			fprintf(stderr, "LIBARCHIVE_ASYNC_IO=%s\n",
			    (t->async_io)?"Enabled":"Disabled");
		} else
			t->async_io = ASYNC_IO;
	}
	return (t);
failed:
	archive_wstring_free(&ws);
