char *curl_escape(const char *string, int inlength)
{
  size_t alloc = (inlength?(size_t)inlength:strlen(string))+1;
  char *ns;
  char *testing_ptr = NULL;
  unsigned char in;
  size_t newlen = alloc;
  int strindex=0;
  size_t length;

  ns = malloc(alloc);
  if(!ns)
    return NULL;

  length = alloc-1;
  while(length--) {
    in = *string;
    if(!(in >= 'a' && in <= 'z') &&
       !(in >= 'A' && in <= 'Z') &&
       !(in >= '0' && in <= '9')) {
      /* encode it */
      newlen += 2; /* the size grows with two, since this'll become a %XX */
      if(newlen > alloc) {
        alloc *= 2;
        testing_ptr = realloc(ns, alloc);
        if(!testing_ptr) {
          free( ns );
          return NULL;
        }
        else {
          ns = testing_ptr;
        }
      }
      snprintf(&ns[strindex], 4, "%%%02X", in);

      strindex+=3;
    }
    else {
      /* just copy this */
      ns[strindex++]=in;
    }
    string++;
  }
  ns[strindex]=0; /* terminate it */
  return ns;
}