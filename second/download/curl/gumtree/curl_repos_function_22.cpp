static int parseconfig(char *filename,
		       struct Configurable *config)
{
  int res;
  FILE *file;
  char configbuffer[4096];
  char filebuffer[256];
  bool usedarg;
  char *home=NULL;
  
  if(!filename || !*filename) {
    /* NULL or no file name attempts to load .curlrc from the homedir! */

#define CURLRC DOT_CHAR "curlrc"

    home = curl_getenv("HOME"); /* portable environment reader */

    if(!home)
      return CURLE_OK;
    if(strlen(home)>(sizeof(filebuffer)-strlen(CURLRC))) {
      free(home);
      return CURLE_OK;
    }

    sprintf(filebuffer, "%s%s%s", home, DIR_CHAR, CURLRC);

    filename = filebuffer;
  }

  if(strcmp(filename,"-"))
    file = fopen(filename, "r");
  else
    file = stdin;
  
  if(file)
  {
    char *line;
    char *tok1;
    char *tok2;

    while (NULL != (line = my_get_line(file)))
    {
      /* lines with # in the fist column is a comment! */
      if ('#' == line[0])
      {
        free(line);
        continue;
      }

      if (NULL == (tok1 = my_get_token(line)))
      {
        free(line);
        continue;
      }
      if ('-' != tok1[0])
      {
        if (config->url)
          free(config->url);
        config->url = tok1;
      }

      while ((NULL != tok1) && ('-' == tok1[0]))
      {
        tok2 = my_get_token(NULL);
        while (NULL == tok2)
        {
          free(line);
          if (NULL == (line = my_get_line(file)))
            break;
          if ('#' == line[0])
            continue;
          tok2 = my_get_token(line);
        }

        res = getparameter(tok1 + 1, tok2, &usedarg, config);
        free(tok1);
        if (!usedarg)
          tok1 = tok2;
        else
        {
          free(tok2);
          break;
        }
        if(res)
          break; /* error detected */
      }

      free(line);
    }
    if(file != stdin)
      fclose(file);
  }
  if(home)
    free(home);
  return CURLE_OK;
}