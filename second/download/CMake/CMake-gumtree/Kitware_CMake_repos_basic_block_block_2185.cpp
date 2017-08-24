(DeleteFileW(ws.c_str()) || GetLastError() == ERROR_FILE_NOT_FOUND ||
      GetLastError() == ERROR_PATH_NOT_FOUND) {
    return true;
  }