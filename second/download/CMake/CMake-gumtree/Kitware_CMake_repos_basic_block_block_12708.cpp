{
	/*
	 * When converting tar archives to cpio archives, it is
	 * essential that each distinct file have a distinct inode
	 * number.  To simplify this, we keep a static count here to
	 * assign fake dev/inode numbers to each tar entry.  Note that
	 * pax format archives may overwrite this with something more
	 * useful.
	 *
	 * Ideally, we would track every file read from the archive so
	 * that we could assign the same dev/ino pair to hardlinks,
	 * but the memory required to store a complete lookup table is
	 * probably not worthwhile just to support the relatively
	 * obscure tar->cpio conversion case.
	 */
	static int default_inode;
	static int default_dev;
	struct tar *tar;
	const char *p;
	const wchar_t *wp;
	int r;
	size_t l, unconsumed = 0;

	/* Assign default device/inode values. */
	archive_entry_set_dev(entry, 1 + default_dev); /* Don't use zero. */
	archive_entry_set_ino(entry, ++default_inode); /* Don't use zero. */
	/* Limit generated st_ino number to 16 bits. */
	if (default_inode >= 0xffff) {
		++default_dev;
		default_inode = 0;
	}

	tar = (struct tar *)(a->format->data);
	tar->entry_offset = 0;
	gnu_clear_sparse_list(tar);
	tar->realsize = -1; /* Mark this as "unset" */

	/* Setup default string conversion. */
	tar->sconv = tar->opt_sconv;
	if (tar->sconv == NULL) {
		if (!tar->init_default_conversion) {
			tar->sconv_default =
			    archive_string_default_conversion_for_read(&(a->archive));
			tar->init_default_conversion = 1;
		}
		tar->sconv = tar->sconv_default;
	}

	r = tar_read_header(a, tar, entry, &unconsumed);

	tar_flush_unconsumed(a, &unconsumed);

	/*
	 * "non-sparse" files are really just sparse files with
	 * a single block.
	 */
	if (tar->sparse_list == NULL) {
		if (gnu_add_sparse_entry(a, tar, 0, tar->entry_bytes_remaining)
		    != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
	} else {
		struct sparse_block *sb;

		for (sb = tar->sparse_list; sb != NULL; sb = sb->next) {
			if (!sb->hole)
				archive_entry_sparse_add_entry(entry,
				    sb->offset, sb->remaining);
		}
	}

	if (r == ARCHIVE_OK && archive_entry_filetype(entry) == AE_IFREG) {
		/*
		 * "Regular" entry with trailing '/' is really
		 * directory: This is needed for certain old tar
		 * variants and even for some broken newer ones.
		 */
		if ((wp = archive_entry_pathname_w(entry)) != NULL) {
			l = wcslen(wp);
			if (l > 0 && wp[l - 1] == L'/') {
				archive_entry_set_filetype(entry, AE_IFDIR);
			}
		} else if ((p = archive_entry_pathname(entry)) != NULL) {
			l = strlen(p);
			if (l > 0 && p[l - 1] == '/') {
				archive_entry_set_filetype(entry, AE_IFDIR);
			}
		}
	}
	return (r);
}