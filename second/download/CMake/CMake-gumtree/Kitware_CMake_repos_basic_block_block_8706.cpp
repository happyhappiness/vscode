{
	case ARCHIVE_WRITE_MAGIC:	return ("archive_write");
	case ARCHIVE_READ_MAGIC:	return ("archive_read");
	case ARCHIVE_WRITE_DISK_MAGIC:	return ("archive_write_disk");
	case ARCHIVE_READ_DISK_MAGIC:	return ("archive_read_disk");
	case ARCHIVE_MATCH_MAGIC:	return ("archive_match");
	default:			return NULL;
	}