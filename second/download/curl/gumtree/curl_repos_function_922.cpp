char *Curl_convert_wchar_to_UTF8(const wchar_t *str_w)
{
  char *str_utf8 = NULL;

  if(str_w) {
    int str_utf8_len = WideCharToMultiByte(CP_UTF8, 0, str_w, -1, NULL,
                                           0, NULL, NULL);
    if(str_utf8_len > 0) {
      str_utf8 = malloc(str_utf8_len * sizeof(wchar_t));
      if(str_utf8) {
        if(WideCharToMultiByte(CP_UTF8, 0, str_w, -1, str_utf8, str_utf8_len,
                               NULL, FALSE) == 0) {
          Curl_safefree(str_utf8);
        }
      }
    }
  }

  return str_utf8;
}