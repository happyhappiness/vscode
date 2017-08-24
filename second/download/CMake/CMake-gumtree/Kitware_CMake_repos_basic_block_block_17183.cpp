{
		case AE_IFREG: h[USTAR_typeflag_offset] = '0' ; break;
		case AE_IFLNK: h[USTAR_typeflag_offset] = '2' ; break;
		case AE_IFCHR: h[USTAR_typeflag_offset] = '3' ; break;
		case AE_IFBLK: h[USTAR_typeflag_offset] = '4' ; break;
		case AE_IFDIR: h[USTAR_typeflag_offset] = '5' ; break;
		case AE_IFIFO: h[USTAR_typeflag_offset] = '6' ; break;
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