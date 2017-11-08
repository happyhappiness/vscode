static char *my_get_line(FILE *fp)
{
  char buf[4096];
  char *nl = NULL;
  char *line = NULL;

  do {
    if(NULL == fgets(buf, sizeof(buf), fp))
      break;
    if(!line) {
      line = strdup(buf);
      if(!line)
        return NULL;
    }
    else {
      char *ptr;
      size_t linelen = strlen(line);
      ptr = realloc(line, linelen + strlen(buf) + 1);
      if(!ptr) {
        Curl_safefree(line);
        return NULL;
      }
      line = ptr;
      strcpy(&line[linelen], buf);
    }
    nl = strchr(line, '\n');
  } while(!nl);

  if(nl)
    *nl = '\0';

  return line;
}