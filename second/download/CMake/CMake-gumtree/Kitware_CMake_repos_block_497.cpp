{
  case OS_MSDOS:
  case OS_OS2:
  case OS_WIN32:
    rar->mode = archive_le32dec(file_header.file_attr);
    if (rar->mode & FILE_ATTRIBUTE_DIRECTORY)
      rar->mode = AE_IFDIR | S_IXUSR | S_IXGRP | S_IXOTH;
    else
      rar->mode = AE_IFREG;
    rar->mode |= S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    break;

  case OS_UNIX:
  case OS_MAC_OS:
  case OS_BEOS:
    rar->mode = archive_le32dec(file_header.file_attr);
    break;

  default:
    archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                      "Unknown file attributes from RAR file's host OS");
    return (ARCHIVE_FATAL);
  }