{
		case AE_IFREG: tartype = '0' ; break;
		case AE_IFLNK: tartype = '2' ; break;
		case AE_IFCHR: tartype = '3' ; break;
		case AE_IFBLK: tartype = '4' ; break;
		case AE_IFDIR: tartype = '5' ; break;
		case AE_IFIFO: tartype = '6' ; break;
		case AE_IFSOCK:
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "tar format cannot archive socket");
			ret = ARCHIVE_FAILED;
			goto exit_write_header;
		default:
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "tar format cannot archive this (mode=0%lo)",
			    (unsigned long)archive_entry_mode(entry));
			ret = ARCHIVE_FAILED;
			goto exit_write_header;
		}