{
      len = MultiByteToWideChar(CP_UTF8,
                                0,
                                *env,
                                -1,
                                ptr,
                                (int) (env_len - (ptr - dst_copy)));
      if (len <= 0) {
        DWORD err = GetLastError();
        uv__free(dst_copy);
        return err;
      }
      *ptr_copy++ = ptr;
      ptr += len;
    }