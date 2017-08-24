{
  DWORD access;
  DWORD share;
  DWORD disposition;
  DWORD attributes = 0;
  HANDLE file;
  int fd, current_umask;
  int flags = req->fs.info.file_flags;

  /* Obtain the active umask. umask() never fails and returns the previous */
  /* umask. */
  current_umask = umask(0);
  umask(current_umask);

  /* convert flags and mode to CreateFile parameters */
  switch (flags & (_O_RDONLY | _O_WRONLY | _O_RDWR)) {
  case _O_RDONLY:
    access = FILE_GENERIC_READ;
    break;
  case _O_WRONLY:
    access = FILE_GENERIC_WRITE;
    break;
  case _O_RDWR:
    access = FILE_GENERIC_READ | FILE_GENERIC_WRITE;
    break;
  default:
    goto einval;
  }

  if (flags & _O_APPEND) {
    access &= ~FILE_WRITE_DATA;
    access |= FILE_APPEND_DATA;
  }

  /*
   * Here is where we deviate significantly from what CRT's _open()
   * does. We indiscriminately use all the sharing modes, to match
   * UNIX semantics. In particular, this ensures that the file can
   * be deleted even whilst it's open, fixing issue #1449.
   */
  share = FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE;

  switch (flags & (_O_CREAT | _O_EXCL | _O_TRUNC)) {
  case 0:
  case _O_EXCL:
    disposition = OPEN_EXISTING;
    break;
  case _O_CREAT:
    disposition = OPEN_ALWAYS;
    break;
  case _O_CREAT | _O_EXCL:
  case _O_CREAT | _O_TRUNC | _O_EXCL:
    disposition = CREATE_NEW;
    break;
  case _O_TRUNC:
  case _O_TRUNC | _O_EXCL:
    disposition = TRUNCATE_EXISTING;
    break;
  case _O_CREAT | _O_TRUNC:
    disposition = CREATE_ALWAYS;
    break;
  default:
    goto einval;
  }

  attributes |= FILE_ATTRIBUTE_NORMAL;
  if (flags & _O_CREAT) {
    if (!((req->fs.info.mode & ~current_umask) & _S_IWRITE)) {
      attributes |= FILE_ATTRIBUTE_READONLY;
    }
  }

  if (flags & _O_TEMPORARY ) {
    attributes |= FILE_FLAG_DELETE_ON_CLOSE | FILE_ATTRIBUTE_TEMPORARY;
    access |= DELETE;
  }

  if (flags & _O_SHORT_LIVED) {
    attributes |= FILE_ATTRIBUTE_TEMPORARY;
  }

  switch (flags & (_O_SEQUENTIAL | _O_RANDOM)) {
  case 0:
    break;
  case _O_SEQUENTIAL:
    attributes |= FILE_FLAG_SEQUENTIAL_SCAN;
    break;
  case _O_RANDOM:
    attributes |= FILE_FLAG_RANDOM_ACCESS;
    break;
  default:
    goto einval;
  }

  /* Setting this flag makes it possible to open a directory. */
  attributes |= FILE_FLAG_BACKUP_SEMANTICS;

  file = CreateFileW(req->file.pathw,
                     access,
                     share,
                     NULL,
                     disposition,
                     attributes,
                     NULL);
  if (file == INVALID_HANDLE_VALUE) {
    DWORD error = GetLastError();
    if (error == ERROR_FILE_EXISTS && (flags & _O_CREAT) &&
        !(flags & _O_EXCL)) {
      /* Special case: when ERROR_FILE_EXISTS happens and O_CREAT was */
      /* specified, it means the path referred to a directory. */
      SET_REQ_UV_ERROR(req, UV_EISDIR, error);
    } else {
      SET_REQ_WIN32_ERROR(req, GetLastError());
    }
    return;
  }

  fd = _open_osfhandle((intptr_t) file, flags);
  if (fd < 0) {
    /* The only known failure mode for _open_osfhandle() is EMFILE, in which
     * case GetLastError() will return zero. However we'll try to handle other
     * errors as well, should they ever occur.
     */
    if (errno == EMFILE)
      SET_REQ_UV_ERROR(req, UV_EMFILE, ERROR_TOO_MANY_OPEN_FILES);
    else if (GetLastError() != ERROR_SUCCESS)
      SET_REQ_WIN32_ERROR(req, GetLastError());
    else
      SET_REQ_WIN32_ERROR(req, UV_UNKNOWN);
    CloseHandle(file);
    return;
  }

  SET_REQ_RESULT(req, fd);
  return;

 einval:
  SET_REQ_UV_ERROR(req, UV_EINVAL, ERROR_INVALID_PARAMETER);
}