(wcsncmp(env, L"PATH=", 5) == 0)
      return &env[5];