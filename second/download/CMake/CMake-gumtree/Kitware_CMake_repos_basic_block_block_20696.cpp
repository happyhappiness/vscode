{
        wcscpy(ptr, required_vars[i].wide_eq);
        ptr += required_vars[i].len;
        var_size = GetEnvironmentVariableW(required_vars[i].wide,
                                           ptr,
                                           (int) (env_len - (ptr - dst)));
        if (var_size != len-1) { /* race condition? */
          uv_fatal_error(GetLastError(), "GetEnvironmentVariableW");
        }
      }