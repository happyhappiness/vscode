{
  wchar_t* name_w;
  wchar_t* value_w;
  int r;

  if (name == NULL || value == NULL)
    return UV_EINVAL;

  r = uv__convert_utf8_to_utf16(name, -1, &name_w);

  if (r != 0)
    return r;

  r = uv__convert_utf8_to_utf16(value, -1, &value_w);

  if (r != 0) {
    uv__free(name_w);
    return r;
  }

  r = SetEnvironmentVariableW(name_w, value_w);
  uv__free(name_w);
  uv__free(value_w);

  if (r == 0)
    return uv_translate_sys_error(GetLastError());

  return 0;
}