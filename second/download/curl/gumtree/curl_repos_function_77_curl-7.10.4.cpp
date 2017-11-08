static int parseconfig(const char *filename,
		       struct Configurable *config)
{
  int res;
  FILE *file;
  char filebuffer[512];
  bool usedarg;
  char *home;
  
  if(!filename || !*filename) {
    /* NULL or no file name attempts to load .curlrc from the homedir! */

#define CURLRC DOT_CHAR "curlrc"

    filename = CURLRC;          /* sensible default */
    home = curl_getenv("HOME"); /* portable environment reader */
    if(home) {
      if(strlen(home)<(sizeof(filebuffer)-strlen(CURLRC))) {

        snprintf(filebuffer, sizeof(filebuffer),
                 "%s%s%s", home, DIR_CHAR, CURLRC);

        filename = filebuffer;
      }
      free(home); /* we've used it, now free it */
    }
  }

  if(strcmp(filename,"-"))
    file = fopen(filename, "r");
  else
    file = stdin;
  
  if(file) {
    char *line;
    char *aline;
    char *option;
    char *param;
    int lineno=0;
    bool alloced_param;

#define isseparator(x) (((x)=='=') || ((x) == ':'))

    while (NULL != (aline = my_get_line(file))) {
      lineno++;
      line = aline;
      alloced_param=FALSE;

      /* lines with # in the fist column is a comment! */
      while(isspace((int)*line))
        line++;

      switch(*line) {
      case '#':
      case '/':
      case '\r':
      case '\n':
      case '*':
      case '\0':
        free(aline);
        continue;
      }

      /* the option keywords starts here */
      option = line;
      while(*line && !isspace((int)*line) && !isseparator(*line))
        line++;
      /* ... and has ended here */

      *line++=0; /* zero terminate, we have a local copy of the data */

#ifdef DEBUG_CONFIG
      fprintf(stderr, "GOT: %s\n", option);
#endif

      /* pass spaces and separator(s) */
      while(isspace((int)*line) || isseparator(*line))
        line++;
      
      /* the parameter starts here (unless quoted) */
      if(*line == '\"') {
        char *ptr;
        /* quoted parameter, do the qoute dance */
        line++;
        param=strdup(line); /* parameter */
        alloced_param=TRUE;

        ptr=param;
        while(*line && (*line != '\"')) {
          if(*line == '\\') {
            char out;
            line++;

            /* default is to output the letter after the backslah */
            switch(out = *line) {
            case '\0':
              continue; /* this'll break out of the loop */
            case 't':
              out='\t';
              break;
            case 'n':
              out='\n';
              break;
            case 'r':
              out='\r';
              break;
            case 'v':
              out='\v';
              break;
            }
            *ptr++=out;
            line++;
          }
          else
            *ptr++=*line++;
        }
        *ptr=0; /* always zero terminate */

      }
      else {
        param=line; /* parameter starts here */
        while(*line && !isspace((int)*line))
          line++;
        *line=0; /* zero terminate */
      }
#ifdef DEBUG_CONFIG
      fprintf(stderr, "PARAM: \"%s\"\n", param);
#endif
      res = getparameter(option, param, &usedarg, config);

      if(*param && !usedarg)
        /* we passed in a parameter that wasn't used! */
        res = PARAM_GOT_EXTRA_PARAMETER;

      if(res != PARAM_OK) {
        /* the help request isn't really an error */
        if(!strcmp(filename, "-")) {
          filename=(char *)"<stdin>";
        }
        if(PARAM_HELP_REQUESTED != res) {
          const char *reason;
          switch(res) {
          default:
          case PARAM_GOT_EXTRA_PARAMETER:
            reason = "had unsupported trailing garbage";
            break;
          case PARAM_OPTION_UNKNOWN:
            reason = "is unknown";
            break;
          case PARAM_OPTION_AMBIGUOUS:
            reason = "is ambiguous";
            break;
          case PARAM_REQUIRES_PARAMETER:
            reason = "requires parameter";
            break;
          case PARAM_BAD_USE:
            reason = "is badly used here";
            break;
          }
          fprintf(stderr, "%s:%d: warning: '%s' %s\n",
                  filename, lineno, option, reason);
        }
      }

      if(alloced_param)
        free(param);

      free(aline);
    }
    if(file != stdin)
      fclose(file);
  }
  return 0;
}