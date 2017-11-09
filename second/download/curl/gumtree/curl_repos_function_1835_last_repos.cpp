static char *unescape_word(struct Curl_easy *data, const char *inputbuff)
{
  char *newp = NULL;
  char *dictp;
  char *ptr;
  size_t len;
  char ch;
  int olen = 0;

  CURLcode result = Curl_urldecode(data, inputbuff, 0, &newp, &len, FALSE);
  if(!newp || result)
    return NULL;

  dictp = malloc(((size_t)len)*2 + 1); /* add one for terminating zero */
  if(dictp) {
    /* According to RFC2229 section 2.2, these letters need to be escaped with
       \[letter] */
    for(ptr = newp;
        (ch = *ptr) != 0;
        ptr++) {
      if((ch <= 32) || (ch == 127) ||
          (ch == '\'') || (ch == '\"') || (ch == '\\')) {
        dictp[olen++] = '\\';
      }
      dictp[olen++] = ch;
    }
    dictp[olen] = 0;
  }
  free(newp);
  return dictp;
}