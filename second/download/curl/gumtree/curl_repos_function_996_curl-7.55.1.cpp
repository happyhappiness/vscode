bool curl_win32_ascii_to_idn(const char *in, char **out)
{
  bool success = FALSE;

  wchar_t *in_w = Curl_convert_UTF8_to_wchar(in);
  if(in_w) {
    size_t in_len = wcslen(in_w) + 1;
    wchar_t unicode[IDN_MAX_LENGTH];
    int chars = IdnToUnicode(0, in_w, curlx_uztosi(in_len),
                             unicode, IDN_MAX_LENGTH);
    free(in_w);
    if(chars) {
      *out = Curl_convert_wchar_to_UTF8(unicode);
      if(*out)
        success = TRUE;
    }
  }

  return success;
}