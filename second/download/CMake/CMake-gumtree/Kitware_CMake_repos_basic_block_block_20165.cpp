{
    assert(errno == EBADF);
    SET_REQ_UV_ERROR(req, UV_EBADF, ERROR_INVALID_HANDLE);
  }