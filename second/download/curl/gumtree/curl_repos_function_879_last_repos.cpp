ParameterError file2string(char **bufp, FILE *file)
{
  char buffer[256];
  char *ptr;
  char *string = NULL;
  size_t stringlen = 0;
  size_t buflen;

  if(file) {
    while(fgets(buffer, sizeof(buffer), file)) {
      ptr = strchr(buffer, '\r');
      if(ptr)
        *ptr = '\0';
      ptr = strchr(buffer, '\n');
      if(ptr)
        *ptr = '\0';
      buflen = strlen(buffer);
      ptr = realloc(string, stringlen + buflen + 1);
      if(!ptr) {
        Curl_safefree(string);
        return PARAM_NO_MEM;
      }
      string = ptr;
      strcpy(string + stringlen, buffer);
      stringlen += buflen;
    }
  }
  *bufp = string;
  return PARAM_OK;
}