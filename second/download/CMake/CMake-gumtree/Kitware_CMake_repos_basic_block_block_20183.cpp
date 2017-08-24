(!(info.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)) {
      SET_REQ_WIN32_ERROR(req, ERROR_ACCESS_DENIED);
      CloseHandle(handle);
      return;
    }