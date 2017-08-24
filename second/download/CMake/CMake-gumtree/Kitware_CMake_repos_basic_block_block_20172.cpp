{
  int fd = req->file.fd;
  int64_t offset = req->fs.info.offset;
  HANDLE handle;
  OVERLAPPED overlapped, *overlapped_ptr;
  LARGE_INTEGER offset_;
  DWORD bytes;
  DWORD error;
  int result;
  unsigned int index;

  VERIFY_FD(fd, req);

  handle = uv__get_osfhandle(fd);

  if (handle == INVALID_HANDLE_VALUE) {
    SET_REQ_WIN32_ERROR(req, ERROR_INVALID_HANDLE);
    return;
  }

  if (offset != -1) {
    memset(&overlapped, 0, sizeof overlapped);
    overlapped_ptr = &overlapped;
  } else {
    overlapped_ptr = NULL;
  }

  index = 0;
  bytes = 0;
  do {
    DWORD incremental_bytes;

    if (offset != -1) {
      offset_.QuadPart = offset + bytes;
      overlapped.Offset = offset_.LowPart;
      overlapped.OffsetHigh = offset_.HighPart;
    }

    result = ReadFile(handle,
                      req->fs.info.bufs[index].base,
                      req->fs.info.bufs[index].len,
                      &incremental_bytes,
                      overlapped_ptr);
    bytes += incremental_bytes;
    ++index;
  } while (result && index < req->fs.info.nbufs);

  if (result || bytes > 0) {
    SET_REQ_RESULT(req, bytes);
  } else {
    error = GetLastError();
    if (error == ERROR_HANDLE_EOF) {
      SET_REQ_RESULT(req, bytes);
    } else {
      SET_REQ_WIN32_ERROR(req, error);
    }
  }
}