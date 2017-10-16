        param = NULL;
      }

#ifdef DEBUG_CONFIG
      fprintf(stderr, "PARAM: \"%s\"\n",(param ? param : "(null)"));
#endif
      res = getparameter(option, param, &usedarg, config);

      if(param && *param && !usedarg)
        /* we passed in a parameter that wasn't used! */
        res = PARAM_GOT_EXTRA_PARAMETER;

      if(res != PARAM_OK) {
        /* the help request isn't really an error */
        if(!strcmp(filename, "-")) {
          filename = (char *)"<stdin>";
        }
        if(PARAM_HELP_REQUESTED != res) {
          const char *reason = param2text(res);
          warnf(config, "%s:%d: warning: '%s' %s\n",
                filename, lineno, option, reason);
        }
      }

      if(alloced_param)
        Curl_safefree(param);
