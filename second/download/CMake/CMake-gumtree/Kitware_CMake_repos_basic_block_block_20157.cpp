(GetLastError() != ERROR_SUCCESS)
      SET_REQ_WIN32_ERROR(req, GetLastError())