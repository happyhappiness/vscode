{
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