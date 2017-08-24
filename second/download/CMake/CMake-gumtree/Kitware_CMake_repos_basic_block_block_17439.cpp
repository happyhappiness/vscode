{
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