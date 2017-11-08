char *curl_unescape(const char *string, int length)
{
  int alloc = (length?length:(int)strlen(string))+1;
  char *ns = malloc(alloc);
  unsigned char in;
  int index=0;
  unsigned int hex;
  char querypart=FALSE; /* everything to the right of a '?' letter is
                           the "query part" where '+' should become ' '.
                           RFC 2316, section 3.10 */
  
  while(--alloc > 0) {
    in = *string;
    if(querypart && ('+' == in))
      in = ' ';
    else if(!querypart && ('?' == in)) {
      /* we have "walked in" to the query part */
      querypart=TRUE;
    }
    else if('%' == in) {
      /* encoded part */
      if(sscanf(string+1, "%02X", &hex)) {
        in = hex;
        string+=2;
        alloc-=2;
      }
    }
    
    ns[index++] = in;
    string++;
  }
  ns[index]=0; /* terminate it */
  return ns;
  
}