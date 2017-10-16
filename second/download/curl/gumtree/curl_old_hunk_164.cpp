        /* the help request isn't really an error */
        if(!strcmp(filename, "-")) {
          filename=(char *)"<stdin>";
        }
        if(PARAM_HELP_REQUESTED != res) {
          const char *reason = param2text(res);
          fprintf(stderr, "%s:%d: warning: '%s' %s\n",
                  filename, lineno, option, reason);
        }
      }

      if(alloced_param)
      {
        free(param);
