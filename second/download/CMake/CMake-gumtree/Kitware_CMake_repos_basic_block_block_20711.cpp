(env = env_block; *env; env++) {
    int len;
    if (strchr(*env, '=')) {
      len = MultiByteToWideChar(CP_UTF8,
                                0,
                                *env,
                                -1,
                                NULL,
                                0);
      if (len <= 0) {
        return GetLastError();
      }
      env_len += len;
      env_block_count++;
    }
  }