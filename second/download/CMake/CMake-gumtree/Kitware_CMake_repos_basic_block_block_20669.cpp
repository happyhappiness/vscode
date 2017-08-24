{
  int ws_len, r;
  WCHAR* ws;

  ws_len = MultiByteToWideChar(CP_UTF8,
                               0,
                               s,
                               -1,
                               NULL,
                               0);
  if (ws_len <= 0) {
    return GetLastError();
  }

  ws = (WCHAR*) uv__malloc(ws_len * sizeof(WCHAR));
  if (ws == NULL) {
    return ERROR_OUTOFMEMORY;
  }

  r = MultiByteToWideChar(CP_UTF8,
                          0,
                          s,
                          -1,
                          ws,
                          ws_len);
  assert(r == ws_len);

  *ws_ptr = ws;
  return 0;
}