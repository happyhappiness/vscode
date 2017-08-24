{
	case ARCHIVE_FORMAT_7ZIP:
		return archive_read_support_format_7zip(a);
		break;
	case ARCHIVE_FORMAT_AR:
		return archive_read_support_format_ar(a);
		break;
	case ARCHIVE_FORMAT_CAB:
		return archive_read_support_format_cab(a);
		break;
	case ARCHIVE_FORMAT_CPIO:
		return archive_read_support_format_cpio(a);
		break;
	case ARCHIVE_FORMAT_ISO9660:
		return archive_read_support_format_iso9660(a);
		break;
	case ARCHIVE_FORMAT_LHA:
		return archive_read_support_format_lha(a);
		break;
	case ARCHIVE_FORMAT_MTREE:
		return archive_read_support_format_mtree(a);
		break;
	case ARCHIVE_FORMAT_RAR:
		return archive_read_support_format_rar(a);
		break;
	case ARCHIVE_FORMAT_TAR:
		return archive_read_support_format_tar(a);
		break;
	case ARCHIVE_FORMAT_XAR:
		return archive_read_support_format_xar(a);
		break;
	case ARCHIVE_FORMAT_ZIP:
		return archive_read_support_format_zip(a);
		break;
	}