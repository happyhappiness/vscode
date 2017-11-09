static bool Curl_isxdigit(char digit)
{
  return ( (digit >= 0x30 && digit <= 0x39) /* 0-9 */
        || (digit >= 0x41 && digit <= 0x46) /* A-F */
        || (digit >= 0x61 && digit <= 0x66) /* a-f */) ? TRUE : FALSE;
}