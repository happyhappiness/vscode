size_t Curl_base64_decode(const char *src, unsigned char **outptr)
{
  int length = 0;
  int equalsTerm = 0;
  int i;
  int numQuantums;
  unsigned char lastQuantum[3];
  size_t rawlen=0;
  unsigned char *newstr;

  *outptr = NULL;

  while((src[length] != '=') && src[length])
    length++;
  /* A maximum of two = padding characters is allowed */
  if(src[length] == '=') {
    equalsTerm++;
    if(src[length+equalsTerm] == '=')
      equalsTerm++;
  }
  numQuantums = (length + equalsTerm) / 4;

  /* Don't allocate a buffer if the decoded length is 0 */
  if (numQuantums <= 0)
    return 0;

  rawlen = (numQuantums * 3) - equalsTerm;

  /* The buffer must be large enough to make room for the last quantum
  (which may be partially thrown out) and the zero terminator. */
  newstr = malloc(rawlen+4);
  if(!newstr)
    return 0;

  *outptr = newstr;

  /* Decode all but the last quantum (which may not decode to a
  multiple of 3 bytes) */
  for(i = 0; i < numQuantums - 1; i++) {
    decodeQuantum((unsigned char *)newstr, src);
    newstr += 3; src += 4;
  }

  /* This final decode may actually read slightly past the end of the buffer
  if the input string is missing pad bytes.  This will almost always be
  harmless. */
  decodeQuantum(lastQuantum, src);
  for(i = 0; i < 3 - equalsTerm; i++)
    newstr[i] = lastQuantum[i];

  newstr[i] = 0; /* zero terminate */
  return rawlen;
}