(DuplicateHandle(GetCurrentProcess(), in, GetCurrentProcess(), out, 0,
                        TRUE, DUPLICATE_SAME_ACCESS)) {
      return ERROR_SUCCESS;
    } else {
      return GetLastError();
    }