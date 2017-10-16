      config->use_resume=TRUE;
      break;
    case 'd':
      /* postfield data */
      {
        char *postdata=NULL;

        if('@' == *nextarg) {
          /* the data begins with a '@' letter, it means that a file name
             or - (stdin) follows */
          FILE *file;

          nextarg++; /* pass the @ */

          if(curlx_strequal("-", nextarg)) {
            file = stdin;
            if(subletter == 'b') /* forced data-binary */
              SET_BINMODE(stdin);
