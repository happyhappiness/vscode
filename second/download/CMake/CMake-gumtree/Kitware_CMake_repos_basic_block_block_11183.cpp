{
	case COMPTYPE_NONE:
		return (cab_read_ahead_cfdata_none(a, avail));
	case COMPTYPE_MSZIP:
		return (cab_read_ahead_cfdata_deflate(a, avail));
	case COMPTYPE_LZX:
		return (cab_read_ahead_cfdata_lzx(a, avail));
	default: /* Unsupported compression. */
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Unsupported CAB compression : %s",
		    cab->entry_cffolder->compname);
		*avail = ARCHIVE_FAILED;
		return (NULL);
	}