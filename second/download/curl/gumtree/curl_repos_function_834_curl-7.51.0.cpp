ParameterError parse_args(struct GlobalConfig *config, int argc,
                          argv_item_t argv[])
{
  int i;
  bool stillflags;
  char *orig_opt = NULL;
  ParameterError result = PARAM_OK;
  struct OperationConfig *operation = config->first;

  for(i = 1, stillflags = TRUE; i < argc && !result; i++) {
    orig_opt = argv[i];

    if(stillflags && ('-' == argv[i][0])) {
      char *nextarg;
      bool passarg;
      char *flag = argv[i];

      if(!strcmp("--", argv[i]))
        /* This indicates the end of the flags and thus enables the
           following (URL) argument to start with -. */
        stillflags = FALSE;
      else {
        nextarg = (i < (argc - 1)) ? argv[i + 1] : NULL;

        result = getparameter(flag, nextarg, &passarg, config, operation);
        if(result == PARAM_NEXT_OPERATION) {
          /* Reset result as PARAM_NEXT_OPERATION is only used here and not
             returned from this function */
          result = PARAM_OK;

          if(operation->url_list && operation->url_list->url) {
            /* Allocate the next config */
            operation->next = malloc(sizeof(struct OperationConfig));
            if(operation->next) {
              /* Initialise the newly created config */
              config_init(operation->next);

              /* Copy the easy handle */
              operation->next->easy = config->easy;

              /* Set the global config pointer */
              operation->next->global = config;

              /* Update the last operation pointer */
              config->last = operation->next;

              /* Move onto the new config */
              operation->next->prev = operation;
              operation = operation->next;
            }
            else
              result = PARAM_NO_MEM;
          }
        }
        else if(!result && passarg)
          i++; /* we're supposed to skip this */
      }
    }
    else {
      bool used;

      /* Just add the URL please */
      result = getparameter((char *)"--url", argv[i], &used, config,
                            operation);
    }
  }

  if(result && result != PARAM_HELP_REQUESTED &&
     result != PARAM_MANUAL_REQUESTED &&
     result != PARAM_VERSION_INFO_REQUESTED &&
     result != PARAM_ENGINES_REQUESTED) {
    const char *reason = param2text(result);

    if(orig_opt && strcmp(":", orig_opt))
      helpf(config->errors, "option %s: %s\n", orig_opt, reason);
    else
      helpf(config->errors, "%s\n", reason);
  }

  return result;
}