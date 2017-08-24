{
  wchar_t* name_w;
  int r;

  if (name == NULL)
    return UV_EINVAL;

  r = uv__convert_utf8_to_utf16(name, -1, &name_w);

  if (r != 0)
    return r;

  r = SetEnvironmentVariableW(name_w, NULL);
  uv__free(name_w);

  if (r == 0)
    return uv_translate_sys_error(GetLastError());

  return 0;
}