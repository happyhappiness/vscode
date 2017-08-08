{
    case ARCHIVE_FORMAT_7ZIP:
      strcpy(str, "7zip");
      break;
    case ARCHIVE_FORMAT_AR:
      strcpy(str, "ar");
      break;
    case ARCHIVE_FORMAT_CAB:
      strcpy(str, "cab");
      break;
    case ARCHIVE_FORMAT_CPIO:
      strcpy(str, "cpio");
      break;
    case ARCHIVE_FORMAT_ISO9660:
      strcpy(str, "iso9660");
      break;
    case ARCHIVE_FORMAT_LHA:
      strcpy(str, "lha");
      break;
    case ARCHIVE_FORMAT_MTREE:
      strcpy(str, "mtree");
      break;
    case ARCHIVE_FORMAT_RAR:
      strcpy(str, "rar");
      break;
    case ARCHIVE_FORMAT_TAR:
      strcpy(str, "tar");
      break;
    case ARCHIVE_FORMAT_XAR:
      strcpy(str, "xar");
      break;
    case ARCHIVE_FORMAT_ZIP:
      strcpy(str, "zip");
      break;
    default:
      archive_set_error(&a->archive, ARCHIVE_ERRNO_PROGRAMMER,
          "Invalid format code specified");
      return (ARCHIVE_FATAL);
  }