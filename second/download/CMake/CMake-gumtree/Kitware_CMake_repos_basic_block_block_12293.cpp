(val[0]) {
			case 'b':
				if (strcmp(val, "block") == 0) {
					archive_entry_set_filetype(entry, AE_IFBLK);
					break;
				}
			case 'c':
				if (strcmp(val, "char") == 0) {
					archive_entry_set_filetype(entry,
						AE_IFCHR);
					break;
				}
			case 'd':
				if (strcmp(val, "dir") == 0) {
					archive_entry_set_filetype(entry,
						AE_IFDIR);
					break;
				}
			case 'f':
				if (strcmp(val, "fifo") == 0) {
					archive_entry_set_filetype(entry,
						AE_IFIFO);
					break;
				}
				if (strcmp(val, "file") == 0) {
					archive_entry_set_filetype(entry,
						AE_IFREG);
					break;
				}
			case 'l':
				if (strcmp(val, "link") == 0) {
					archive_entry_set_filetype(entry,
						AE_IFLNK);
					break;
				}
			default:
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_FILE_FORMAT,
				    "Unrecognized file type \"%s\"; "
				    "assuming \"file\"", val);
				archive_entry_set_filetype(entry, AE_IFREG);
				return (ARCHIVE_WARN);
			}