(fd <= 2) {
    /* In order to avoid closing a stdio file descriptor 0-2, duplicate the
     * underlying OS handle and forget about the original fd.
     * We could also opt to use the original OS handle and just never close it,
     * but then there would be no reliable way to cancel pending read operations
     * upon close.
     */
    if (!DuplicateHandle(INVALID_HANDLE_VALUE,
                         handle,
                         INVALID_HANDLE_VALUE,
                         &handle,
                         0,
                         FALSE,
                         DUPLICATE_SAME_ACCESS))
      return uv_translate_sys_error(GetLastError());
    fd = -1;
  }