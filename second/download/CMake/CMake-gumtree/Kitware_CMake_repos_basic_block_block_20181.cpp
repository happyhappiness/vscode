{
      DWORD error = GetLastError();
      if (error == ERROR_SYMLINK_NOT_SUPPORTED)
        error = ERROR_ACCESS_DENIED;
      SET_REQ_WIN32_ERROR(req, error);
      CloseHandle(handle);
      return;
    }