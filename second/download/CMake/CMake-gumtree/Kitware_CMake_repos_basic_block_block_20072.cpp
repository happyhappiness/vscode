{
      res = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                           FORMAT_MESSAGE_FROM_SYSTEM |
                           FORMAT_MESSAGE_IGNORE_INSERTS, NULL, errorno,
                           0, (LPSTR) &lib->errmsg, 0, NULL);
    }