CURLcode Curl_rand_hex(struct Curl_easy *data, unsigned char *rnd,
                       size_t num)
{
  CURLcode result = CURLE_BAD_FUNCTION_ARGUMENT;
  const char *hex = "0123456789abcdef";
  unsigned char buffer[128];
  unsigned char *bufp = buffer;
  DEBUGASSERT(num > 1);

  if((num/2 >= sizeof(buffer)) || !(num&1))
    /* make sure it fits in the local buffer and that it is an odd number! */
    return CURLE_BAD_FUNCTION_ARGUMENT;

  num--; /* save one for zero termination */

  result = Curl_rand(data, buffer, num/2);
  if(result)
    return result;

  while(num) {
    *rnd++ = hex[(*bufp & 0xF0)>>4];
    *rnd++ = hex[*bufp & 0x0F];
    bufp++;
    num -= 2;
  }
  *rnd = 0;

  return result;
}