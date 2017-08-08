{
			case LZMA_MEM_ERROR:
				archive_set_error(&a->archive,
				    ENOMEM,
				    "Internal error initializing "
				    "compression library: "
				    "Cannot allocate memory");
				break;
			case LZMA_OPTIONS_ERROR:
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Internal error initializing "
				    "compression library: "
				    "Invalid or unsupported options");
				break;
			default:
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Internal error initializing "
				    "lzma library");
				break;
			}