{
	case AE_IFREG:
		/* Only regular files have non-zero size. */
		break;
	case AE_IFDIR:
		archive_entry_set_size(entry, 0);
		/* Don't bother trying to recreate '.' */
		if (strcmp(name, ".") == 0  ||  strcmp(name, "./") == 0)
			return (ARCHIVE_OK);
		break;
	case AE_IFIFO:
	case AE_IFCHR:
	case AE_IFBLK:
		/* All other file types have zero size in the archive. */
		archive_entry_set_size(entry, 0);
		break;
	default:
		archive_entry_set_size(entry, 0);
		if (archive_entry_hardlink(entry) == NULL &&
		    archive_entry_symlink(entry) == NULL) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "shar format cannot archive this");
			return (ARCHIVE_WARN);
		}
	}