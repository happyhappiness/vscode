{
		struct archive_entry *pax_attr_entry;
		time_t s;
		int64_t uid, gid;
		int mode;

		pax_attr_entry = archive_entry_new2(&a->archive);
		p = entry_name.s;
		archive_entry_set_pathname(pax_attr_entry,
		    build_pax_attribute_name(pax_entry_name, p));
		archive_entry_set_size(pax_attr_entry,
		    archive_strlen(&(pax->pax_header)));
		/* Copy uid/gid (but clip to ustar limits). */
		uid = archive_entry_uid(entry_main);
		if (uid >= 1 << 18)
			uid = (1 << 18) - 1;
		archive_entry_set_uid(pax_attr_entry, uid);
		gid = archive_entry_gid(entry_main);
		if (gid >= 1 << 18)
			gid = (1 << 18) - 1;
		archive_entry_set_gid(pax_attr_entry, gid);
		/* Copy mode over (but not setuid/setgid bits) */
		mode = archive_entry_mode(entry_main);
#ifdef S_ISUID
		mode &= ~S_ISUID;
#endif
#ifdef S_ISGID
		mode &= ~S_ISGID;
#endif
#ifdef S_ISVTX
		mode &= ~S_ISVTX;
#endif
		archive_entry_set_mode(pax_attr_entry, mode);

		/* Copy uname/gname. */
		archive_entry_set_uname(pax_attr_entry,
		    archive_entry_uname(entry_main));
		archive_entry_set_gname(pax_attr_entry,
		    archive_entry_gname(entry_main));

		/* Copy mtime, but clip to ustar limits. */
		s = archive_entry_mtime(entry_main);
		if (s < 0) { s = 0; }
		if (s >= 0x7fffffff) { s = 0x7fffffff; }
		archive_entry_set_mtime(pax_attr_entry, s, 0);

		/* Standard ustar doesn't support atime. */
		archive_entry_set_atime(pax_attr_entry, 0, 0);

		/* Standard ustar doesn't support ctime. */
		archive_entry_set_ctime(pax_attr_entry, 0, 0);

		r = __archive_write_format_header_ustar(a, paxbuff,
		    pax_attr_entry, 'x', 1, NULL);

		archive_entry_free(pax_attr_entry);

		/* Note that the 'x' header shouldn't ever fail to format */
		if (r < ARCHIVE_WARN) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "archive_write_pax_header: "
			    "'x' header failed?!  This can't happen.\n");
			return (ARCHIVE_FATAL);
		} else if (r < ret)
			ret = r;
		r = __archive_write_output(a, paxbuff, 512);
		if (r != ARCHIVE_OK) {
			sparse_list_clear(pax);
			pax->entry_bytes_remaining = 0;
			pax->entry_padding = 0;
			return (ARCHIVE_FATAL);
		}

		pax->entry_bytes_remaining = archive_strlen(&(pax->pax_header));
		pax->entry_padding =
		    0x1ff & (-(int64_t)pax->entry_bytes_remaining);

		r = __archive_write_output(a, pax->pax_header.s,
		    archive_strlen(&(pax->pax_header)));
		if (r != ARCHIVE_OK) {
			/* If a write fails, we're pretty much toast. */
			return (ARCHIVE_FATAL);
		}
		/* Pad out the end of the entry. */
		r = __archive_write_nulls(a, (size_t)pax->entry_padding);
		if (r != ARCHIVE_OK) {
			/* If a write fails, we're pretty much toast. */
			return (ARCHIVE_FATAL);
		}
		pax->entry_bytes_remaining = pax->entry_padding = 0;
	}