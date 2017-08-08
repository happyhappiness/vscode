{
		case AE_IFREG: case AE_IFDIR:
			break;
		case AE_IFLNK:
			h[V7TAR_typeflag_offset] = '2';
			break;
		case AE_IFCHR:
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "tar format cannot archive character device");
			return (ARCHIVE_FAILED);
		case AE_IFBLK:
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "tar format cannot archive block device");
			return (ARCHIVE_FAILED);
		case AE_IFIFO:
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "tar format cannot archive fifo");
			return (ARCHIVE_FAILED);
		case AE_IFSOCK:
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "tar format cannot archive socket");
			return (ARCHIVE_FAILED);
		default:
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "tar format cannot archive this (mode=0%lo)",
			    (unsigned long)archive_entry_mode(entry));
			ret = ARCHIVE_FAILED;
		}