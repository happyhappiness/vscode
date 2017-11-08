ParameterError file2string(char **bufp, FILE *file)
{
  char buffer[256];
  char *ptr;
  char *string = NULL;
  size_t stringlen = 0;
  size_t buflen;

  if(file) {
    while(fgets(buffer, sizeof(buffer), file)) {
      if((ptr = strchr(buffer, '\r')) != NULL)
        *ptr = '\0';
      if((ptr = strchr(buffer, '\n')) != NULL)
        *ptr = '\0';
      buflen = strlen(buffer);
      if((ptr = realloc(string, stringlen+buflen+1)) == NULL) {
        Curl_safefree(string);
        return PARAM_NO_MEM;
      }
      string = ptr;
      strcpy(string+stringlen, buffer);
      stringlen += buflen;
    }
  }
  *bufp = string;
  return PARAM_OK;
}