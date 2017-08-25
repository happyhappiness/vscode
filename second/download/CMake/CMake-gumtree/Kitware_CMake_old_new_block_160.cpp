{
			case LZMADEC_OK:
				break;
			default:
				archive_set_error(&(a->archive),
				    ARCHIVE_ERRNO_MISC,
				    "Failed to clean up lzmadec decompressor");
				return (ARCHIVE_FATAL);
			}