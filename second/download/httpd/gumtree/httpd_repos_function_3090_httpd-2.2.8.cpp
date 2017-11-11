static char *apr_os_strerror(char* buf, apr_size_t bufsize, int err)
{
  char result[200];
  unsigned char message[HUGE_STRING_LEN];
  ULONG len;
  char *pos;
  int c;
  
  if (err >= 10000 && err < 12000) {  /* socket error codes */
      return stuffbuffer(buf, bufsize,
                         strerror(apr_canonical_error(err+APR_OS_START_SYSERR)));
  } 
  else if (DosGetMessage(NULL, 0, message, HUGE_STRING_LEN, err,
			 "OSO001.MSG", &len) == 0) {
      len--;
      message[len] = 0;
      pos = result;
  
      if (len >= sizeof(result))
        len = sizeof(result-1);

      for (c=0; c<len; c++) {
	  /* skip multiple whitespace */
          while (apr_isspace(message[c]) && apr_isspace(message[c+1]))
              c++;
          *(pos++) = apr_isspace(message[c]) ? ' ' : message[c];
      }
  
      *pos = 0;
  } 
  else {
      sprintf(result, "OS/2 error %d", err);
  }

  /* Stuff the string into the caller supplied buffer, then return 
   * a pointer to it.
   */
  return stuffbuffer(buf, bufsize, result);  
}