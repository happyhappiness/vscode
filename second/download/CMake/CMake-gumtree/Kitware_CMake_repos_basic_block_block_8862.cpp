{
#if defined(_WIN32) && !defined(__CYGWIN__)
		r = path_excluded(a, 0, archive_entry_pathname_w(entry));
#else
		r = path_excluded(a, 1, archive_entry_pathname(entry));
#endif
		if (r != 0)
			return (r);
	}