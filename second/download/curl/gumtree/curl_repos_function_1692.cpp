static char *unescape_word(struct SessionHandle *data, const char *inputbuff)
{
  char *newp;
  char *dictp;
  char *ptr;
  int len;
  char byte;
  int olen=0;

  newp = curl_easy_unescape(data, inputbuff, 0, &len);
  if(!newp)
    return NULL;

  dictp = malloc(((size_t)len)*2 + 1); /* add one for terminating zero */
  if(dictp) {
    /* According to RFC2229 section 2.2, these letters need to be escaped with
       \[letter] */
    for(ptr = newp;
        (byte = *ptr) != 0;
        ptr++) {
      if((byte <= 32) || (byte == 127) ||
          (byte == '\'') || (byte == '\"') || (byte == '\\')) {
        dictp[olen++] = '\\';
      }
      dictp[olen++] = byte;
    }
    dictp[olen]=0;
  }
  free(newp);
  return dictp;
}