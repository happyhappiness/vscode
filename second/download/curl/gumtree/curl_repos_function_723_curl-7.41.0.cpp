static unsigned char hex_to_uint(const char *s)
{
  int v[2];
  int i;
  for(i = 0; i < 2; ++i) {
    v[i] = Curl_raw_toupper(s[i]);
    if('0' <= v[i] && v[i] <= '9') {
      v[i] -= '0';
    }
    else if('A' <= v[i] && v[i] <= 'Z') {
      v[i] -= 'A'-10;
    }
  }
  return (unsigned char)((v[0] << 4) | v[1]);
}