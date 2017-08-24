{
          DWORD access = (i == 0) ? FILE_GENERIC_READ :
                                    FILE_GENERIC_WRITE | FILE_READ_ATTRIBUTES;

          err = uv__create_nul_handle(&CHILD_STDIO_HANDLE(buffer, i),
                                      access);
          if (err)
            goto error;

          CHILD_STDIO_CRT_FLAGS(buffer, i) = FOPEN | FDEV;
        }