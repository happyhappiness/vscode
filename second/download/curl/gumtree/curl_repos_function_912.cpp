int curl_win32_idn_to_ascii(const char *in, char **out)
{
  wchar_t *in_w = Curl_convert_UTF8_to_wchar(in);
  if(in_w) {
    wchar_t punycode[IDN_MAX_LENGTH];
    if(IdnToAscii(0, in_w, -1, punycode, IDN_MAX_LENGTH) == 0) {
      wprintf(L"ERROR %d converting to Punycode\n", GetLastError());
      free(in_w);
      return 0;
    }
    free(in_w);

    *out = Curl_convert_wchar_to_UTF8(punycode);
    if(!*out)
      return 0;
  }
  return 1;
}