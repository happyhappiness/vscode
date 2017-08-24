{
    /* Construct the environment variable name and set it. */
    env_var[0] = L'=';
    env_var[1] = drive_letter;
    env_var[2] = L':';
    env_var[3] = L'\0';

    if (!SetEnvironmentVariableW(env_var, utf16_buffer)) {
      return uv_translate_sys_error(GetLastError());
    }
  }