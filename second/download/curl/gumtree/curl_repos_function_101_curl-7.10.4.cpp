char *curl_escape(const char *string, int length)
{
  int alloc = (length?length:(int)strlen(string))+1;  
  char *ns = malloc(alloc);
  char *testing_ptr = NULL;
  unsigned char in;
  int newlen = alloc;
  int index=0;

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
      sprintf(&ns[index], "%%%02X", in);

      index+=3;
    }
    else {
      /* just copy this */
      ns[index++]=in;
    }
    string++;
  }
  ns[index]=0; /* terminate it */
  return ns;
}