{
	struct match_file *f;
	const void *pathname;
	time_t sec;
	long nsec;

	/*
	 * If this file/dir is excluded by a time comparison, skip it.
	 */
	if (a->newer_ctime_filter) {
		/* If ctime is not set, use mtime instead. */
		if (archive_entry_ctime_is_set(entry))
			sec = archive_entry_ctime(entry);
		else
			sec = archive_entry_mtime(entry);
		if (sec < a->newer_ctime_sec)
			return (1); /* Too old, skip it. */
		if (sec == a->newer_ctime_sec) {
			if (archive_entry_ctime_is_set(entry))
				nsec = archive_entry_ctime_nsec(entry);
			else
				nsec = archive_entry_mtime_nsec(entry);
			if (nsec < a->newer_ctime_nsec)
				return (1); /* Too old, skip it. */
			if (nsec == a->newer_ctime_nsec &&
			    (a->newer_ctime_filter & ARCHIVE_MATCH_EQUAL)
			      == 0)
				return (1); /* Equal, skip it. */
		}
	}
	if (a->older_ctime_filter) {
		/* If ctime is not set, use mtime instead. */
		if (archive_entry_ctime_is_set(entry))
			sec = archive_entry_ctime(entry);
		else
			sec = archive_entry_mtime(entry);
		if (sec > a->older_ctime_sec)
			return (1); /* Too new, skip it. */
		if (sec == a->older_ctime_sec) {
			if (archive_entry_ctime_is_set(entry))
				nsec = archive_entry_ctime_nsec(entry);
			else
				nsec = archive_entry_mtime_nsec(entry);
			if (nsec > a->older_ctime_nsec)
				return (1); /* Too new, skip it. */
			if (nsec == a->older_ctime_nsec &&
			    (a->older_ctime_filter & ARCHIVE_MATCH_EQUAL)
			      == 0)
				return (1); /* Equal, skip it. */
		}
	}
	if (a->newer_mtime_filter) {
		sec = archive_entry_mtime(entry);
		if (sec < a->newer_mtime_sec)
			return (1); /* Too old, skip it. */
		if (sec == a->newer_mtime_sec) {
			nsec = archive_entry_mtime_nsec(entry);
			if (nsec < a->newer_mtime_nsec)
				return (1); /* Too old, skip it. */
			if (nsec == a->newer_mtime_nsec &&
			    (a->newer_mtime_filter & ARCHIVE_MATCH_EQUAL)
			       == 0)
				return (1); /* Equal, skip it. */
		}
	}
	if (a->older_mtime_filter) {
		sec = archive_entry_mtime(entry);
		if (sec > a->older_mtime_sec)
			return (1); /* Too new, skip it. */
		nsec = archive_entry_mtime_nsec(entry);
		if (sec == a->older_mtime_sec) {
			if (nsec > a->older_mtime_nsec)
				return (1); /* Too new, skip it. */
			if (nsec == a->older_mtime_nsec &&
			    (a->older_mtime_filter & ARCHIVE_MATCH_EQUAL)
			       == 0)
				return (1); /* Equal, skip it. */
		}
	}

	/* If there is no exclusion list, include the file. */
	if (a->exclusion_entry_list.count == 0)
		return (0);

#if defined(_WIN32) && !defined(__CYGWIN__)
	pathname = archive_entry_pathname_w(entry);
	a->exclusion_tree.rbt_ops = &rb_ops_wcs;
#else
	(void)rb_ops_wcs;
	pathname = archive_entry_pathname(entry);
	a->exclusion_tree.rbt_ops = &rb_ops_mbs;
#endif
	if (pathname == NULL)
		return (0);

	f = (struct match_file *)__archive_rb_tree_find_node(
		&(a->exclusion_tree), pathname);
	/* If the file wasn't rejected, include it. */
	if (f == NULL)
		return (0);

	if (f->flag & ARCHIVE_MATCH_CTIME) {
		sec = archive_entry_ctime(entry);
		if (f->ctime_sec > sec) {
			if (f->flag & ARCHIVE_MATCH_OLDER)
				return (1);
		} else if (f->ctime_sec < sec) {
			if (f->flag & ARCHIVE_MATCH_NEWER)
				return (1);
		} else {
			nsec = archive_entry_ctime_nsec(entry);
			if (f->ctime_nsec > nsec) {
				if (f->flag & ARCHIVE_MATCH_OLDER)
					return (1);
			} else if (f->ctime_nsec < nsec) {
				if (f->flag & ARCHIVE_MATCH_NEWER)
					return (1);
			} else if (f->flag & ARCHIVE_MATCH_EQUAL)
				return (1);
		}
	}
	if (f->flag & ARCHIVE_MATCH_MTIME) {
		sec = archive_entry_mtime(entry);
		if (f->mtime_sec > sec) {
			if (f->flag & ARCHIVE_MATCH_OLDER)
				return (1);
		} else if (f->mtime_sec < sec) {
			if (f->flag & ARCHIVE_MATCH_NEWER)
				return (1);
		} else {
			nsec = archive_entry_mtime_nsec(entry);
			if (f->mtime_nsec > nsec) {
				if (f->flag & ARCHIVE_MATCH_OLDER)
					return (1);
			} else if (f->mtime_nsec < nsec) {
				if (f->flag & ARCHIVE_MATCH_NEWER)
					return (1);
			} else if (f->flag & ARCHIVE_MATCH_EQUAL)
				return (1);
		}
	}
	return (0);
}