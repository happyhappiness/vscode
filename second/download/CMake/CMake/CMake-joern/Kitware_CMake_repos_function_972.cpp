static int
make_file_entry(struct archive_write *a, xmlTextWriterPtr writer,
    struct file *file)
{
	struct xar *xar;
	const char *filetype, *filelink, *fflags;
	struct archive_string linkto;
	struct heap_data *heap;
	unsigned char *tmp;
	const char *p;
	size_t len;
	int r, r2, l, ll;

	xar = (struct xar *)a->format_data;
	r2 = ARCHIVE_OK;

	/*
	 * Make a file name entry, "<name>".
	 */
	l = ll = archive_strlen(&(file->basename));
	tmp = malloc(l);
	if (tmp == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate memory");
		return (ARCHIVE_FATAL);
	}
	r = UTF8Toisolat1(tmp, &l, BAD_CAST(file->basename.s), &ll);
	free(tmp);
	if (r < 0) {
		r = xmlTextWriterStartElement(writer, BAD_CAST("name"));
		if (r < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "xmlTextWriterStartElement() failed: %d", r);
			return (ARCHIVE_FATAL);
		}
		r = xmlTextWriterWriteAttribute(writer,
		    BAD_CAST("enctype"), BAD_CAST("base64"));
		if (r < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "xmlTextWriterWriteAttribute() failed: %d", r);
			return (ARCHIVE_FATAL);
		}
		r = xmlTextWriterWriteBase64(writer, file->basename.s,
		    0, archive_strlen(&(file->basename)));
		if (r < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "xmlTextWriterWriteBase64() failed: %d", r);
			return (ARCHIVE_FATAL);
		}
		r = xmlTextWriterEndElement(writer);
		if (r < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "xmlTextWriterEndElement() failed: %d", r);
			return (ARCHIVE_FATAL);
		}
	} else {
		r = xmlwrite_string(a, writer, "name", file->basename.s);
		if (r < 0)
			return (ARCHIVE_FATAL);
	}

	/*
	 * Make a file type entry, "<type>".
	 */
	filelink = NULL;
	archive_string_init(&linkto);
	switch (archive_entry_filetype(file->entry)) {
	case AE_IFDIR:
		filetype = "directory"; break;
	case AE_IFLNK:
		filetype = "symlink"; break;
	case AE_IFCHR:
		filetype = "character special"; break;
	case AE_IFBLK:
		filetype = "block special"; break;
	case AE_IFSOCK:
		filetype = "socket"; break;
	case AE_IFIFO:
		filetype = "fifo"; break;
	case AE_IFREG:
	default:
		if (file->hardlink_target != NULL) {
			filetype = "hardlink";
			filelink = "link";
			if (file->hardlink_target == file)
				archive_strcpy(&linkto, "original");
			else
				archive_string_sprintf(&linkto, "%d",
				    file->hardlink_target->id);
		} else
			filetype = "file";
		break;
	}
	r = xmlwrite_string_attr(a, writer, "type", filetype,
	    filelink, linkto.s);
	archive_string_free(&linkto);
	if (r < 0)
		return (ARCHIVE_FATAL);

	/*
	 * On a virtual directory, we record "name" and "type" only.
	 */
	if (file->virtual)
		return (ARCHIVE_OK);

	switch (archive_entry_filetype(file->entry)) {
	case AE_IFLNK:
		/*
		 * xar utility has checked a file type, which
		 * a symbolic-link file has referenced.
		 * For example:
		 *   <link type="directory">../ref/</link>
		 *   The symlink target file is "../ref/" and its
		 *   file type is a directory.
		 *
		 *   <link type="file">../f</link>
		 *   The symlink target file is "../f" and its
		 *   file type is a regular file.
		 *
		 * But our implementation cannot do it, and then we
		 * always record that a attribute "type" is "broken",
		 * for example:
		 *   <link type="broken">foo/bar</link>
		 *   It means "foo/bar" is not reachable.
		 */
		r = xmlwrite_string_attr(a, writer, "link",
		    file->symlink.s,
		    "type", "broken");
		if (r < 0)
			return (ARCHIVE_FATAL);
		break;
	case AE_IFCHR:
	case AE_IFBLK:
		r = xmlTextWriterStartElement(writer, BAD_CAST("device"));
		if (r < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "xmlTextWriterStartElement() failed: %d", r);
			return (ARCHIVE_FATAL);
		}
		r = xmlwrite_fstring(a, writer, "major",
		    "%d", archive_entry_rdevmajor(file->entry));
		if (r < 0)
			return (ARCHIVE_FATAL);
		r = xmlwrite_fstring(a, writer, "minor",
		    "%d", archive_entry_rdevminor(file->entry));
		if (r < 0)
			return (ARCHIVE_FATAL);
		r = xmlTextWriterEndElement(writer);
		if (r < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "xmlTextWriterEndElement() failed: %d", r);
			return (ARCHIVE_FATAL);
		}
		break;
	default:
		break;
	}

	/*
	 * Make a inode entry, "<inode>".
	 */
	r = xmlwrite_fstring(a, writer, "inode",
	    "%jd", archive_entry_ino64(file->entry));
	if (r < 0)
		return (ARCHIVE_FATAL);
	if (archive_entry_dev(file->entry) != 0) {
		r = xmlwrite_fstring(a, writer, "deviceno",
		    "%d", archive_entry_dev(file->entry));
		if (r < 0)
			return (ARCHIVE_FATAL);
	}

	/*
	 * Make a file mode entry, "<mode>".
	 */
	r = xmlwrite_mode(a, writer, "mode",
	    archive_entry_mode(file->entry));
	if (r < 0)
		return (ARCHIVE_FATAL);

	/*
	 * Make a user entry, "<uid>" and "<user>.
	 */
	r = xmlwrite_fstring(a, writer, "uid",
	    "%d", archive_entry_uid(file->entry));
	if (r < 0)
		return (ARCHIVE_FATAL);
	r = archive_entry_uname_l(file->entry, &p, &len, xar->sconv);
	if (r != 0) {
		if (errno == ENOMEM) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for Uname");
			return (ARCHIVE_FATAL);
		}
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT,
		    "Can't translate uname '%s' to UTF-8",
		    archive_entry_uname(file->entry));
		r2 = ARCHIVE_WARN;
	}
	if (len > 0) {
		r = xmlwrite_string(a, writer, "user", p);
		if (r < 0)
			return (ARCHIVE_FATAL);
	}

	/*
	 * Make a group entry, "<gid>" and "<group>.
	 */
	r = xmlwrite_fstring(a, writer, "gid",
	    "%d", archive_entry_gid(file->entry));
	if (r < 0)
		return (ARCHIVE_FATAL);
	r = archive_entry_gname_l(file->entry, &p, &len, xar->sconv);
	if (r != 0) {
		if (errno == ENOMEM) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for Gname");
			return (ARCHIVE_FATAL);
		}
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT,
		    "Can't translate gname '%s' to UTF-8",
		    archive_entry_gname(file->entry));
		r2 = ARCHIVE_WARN;
	}
	if (len > 0) {
		r = xmlwrite_string(a, writer, "group", p);
		if (r < 0)
			return (ARCHIVE_FATAL);
	}

	/*
	 * Make a ctime entry, "<ctime>".
	 */
	if (archive_entry_ctime_is_set(file->entry)) {
		r = xmlwrite_time(a, writer, "ctime",
		    archive_entry_ctime(file->entry), 1);
		if (r < 0)
			return (ARCHIVE_FATAL);
	}

	/*
	 * Make a mtime entry, "<mtime>".
	 */
	if (archive_entry_mtime_is_set(file->entry)) {
		r = xmlwrite_time(a, writer, "mtime",
		    archive_entry_mtime(file->entry), 1);
		if (r < 0)
			return (ARCHIVE_FATAL);
	}

	/*
	 * Make a atime entry, "<atime>".
	 */
	if (archive_entry_atime_is_set(file->entry)) {
		r = xmlwrite_time(a, writer, "atime",
		    archive_entry_atime(file->entry), 1);
		if (r < 0)
			return (ARCHIVE_FATAL);
	}

	/*
	 * Make fflags entries, "<flags>" and "<ext2>".
	 */
	fflags = archive_entry_fflags_text(file->entry);
	if (fflags != NULL) {
		r = make_fflags_entry(a, writer, "flags", fflags);
		if (r < 0)
			return (r);
		r = make_fflags_entry(a, writer, "ext2", fflags);
		if (r < 0)
			return (r);
	}

	/*
	 * Make extended attribute entries, "<ea>".
	 */
	archive_entry_xattr_reset(file->entry);
	for (heap = file->xattr.first; heap != NULL; heap = heap->next) {
		const char *name;
		const void *value;
		size_t size;

		archive_entry_xattr_next(file->entry,
		    &name, &value, &size);
		r = xmlTextWriterStartElement(writer, BAD_CAST("ea"));
		if (r < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "xmlTextWriterStartElement() failed: %d", r);
			return (ARCHIVE_FATAL);
		}
		r = xmlTextWriterWriteFormatAttribute(writer,
		    BAD_CAST("id"), "%d", heap->id);
		if (r < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "xmlTextWriterWriteAttribute() failed: %d", r);
			return (ARCHIVE_FATAL);
		}
		r = xmlwrite_heap(a, writer, heap);
		if (r < 0)
			return (ARCHIVE_FATAL);
		r = xmlwrite_string(a, writer, "name", name);
		if (r < 0)
			return (ARCHIVE_FATAL);

		r = xmlTextWriterEndElement(writer);
		if (r < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "xmlTextWriterEndElement() failed: %d", r);
			return (ARCHIVE_FATAL);
		}
	}

	/*
	 * Make a file data entry, "<data>".
	 */
	if (file->data.length > 0) {
		r = xmlTextWriterStartElement(writer, BAD_CAST("data"));
		if (r < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "xmlTextWriterStartElement() failed: %d", r);
			return (ARCHIVE_FATAL);
		}

		r = xmlwrite_heap(a, writer, &(file->data));
		if (r < 0)
			return (ARCHIVE_FATAL);

		r = xmlTextWriterEndElement(writer);
		if (r < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "xmlTextWriterEndElement() failed: %d", r);
			return (ARCHIVE_FATAL);
		}
	}

	if (archive_strlen(&file->script) > 0) {
		r = xmlTextWriterStartElement(writer, BAD_CAST("content"));
		if (r < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "xmlTextWriterStartElement() failed: %d", r);
			return (ARCHIVE_FATAL);
		}

		r = xmlwrite_string(a, writer,
		    "interpreter", file->script.s);
		if (r < 0)
			return (ARCHIVE_FATAL);

		r = xmlwrite_string(a, writer, "type", "script");
		if (r < 0)
			return (ARCHIVE_FATAL);

		r = xmlTextWriterEndElement(writer);
		if (r < 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "xmlTextWriterEndElement() failed: %d", r);
			return (ARCHIVE_FATAL);
		}
	}

	return (r2);
}