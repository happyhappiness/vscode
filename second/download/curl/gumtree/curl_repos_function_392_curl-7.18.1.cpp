char *curl_easy_escape(CURL *handle, const char *string, int inlength)
{
  size_t alloc = (inlength?(size_t)inlength:strlen(string))+1;
  char *ns;
  char *testing_ptr = NULL;
  unsigned char in; /* we need to treat the characters unsigned */
  size_t newlen = alloc;
  int strindex=0;
  size_t length;

#ifndef CURL_DOES_CONVERSIONS
  /* avoid compiler warnings */
  (void)handle;
#endif
  ns = malloc(alloc);
  if(!ns)
    return NULL;

  length = alloc-1;
  while(length--) {
    in = *string;

    /* Portable character check (remember EBCDIC). Do not use isalnum() because
       its behavior is altered by the current locale. */

    switch (in) {
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    case 'a': case 'b': case 'c': case 'd': case 'e':
    case 'f': case 'g': case 'h': case 'i': case 'j':
    case 'k': case 'l': case 'm': case 'n': case 'o':
    case 'p': case 'q': case 'r': case 's': case 't':
    case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
    case 'A': case 'B': case 'C': case 'D': case 'E':
    case 'F': case 'G': case 'H': case 'I': case 'J':
    case 'K': case 'L': case 'M': case 'N': case 'O':
    case 'P': case 'Q': case 'R': case 'S': case 'T':
    case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z':
      /* just copy this */
      ns[strindex++]=in;
      break;
    default:
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

#ifdef CURL_DOES_CONVERSIONS
/* escape sequences are always in ASCII so convert them on non-ASCII hosts */
      if(!handle ||
          (Curl_convert_to_network(handle, &in, 1) != CURLE_OK)) {
        /* Curl_convert_to_network calls failf if unsuccessful */
        free(ns);
        return NULL;
      }
#endif /* CURL_DOES_CONVERSIONS */

      snprintf(&ns[strindex], 4, "%%%02X", in);

      strindex+=3;
      break;
    }
    string++;
  }
  ns[strindex]=0; /* terminate it */
  return ns;
}