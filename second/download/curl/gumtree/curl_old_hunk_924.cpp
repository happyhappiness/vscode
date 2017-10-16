      {
        /* byte range requested */
        char *tmp_range;
        tmp_range = nextarg;
        while(*tmp_range != '\0') {
          if(!ISDIGIT(*tmp_range) && *tmp_range != '-' && *tmp_range != ',') {
            warnf(config,"Invalid character is found in given range. "
                  "A specified range MUST have only digits in "
                  "\'start\'-\'stop\'. The server's response to this "
                  "request is uncertain.\n");
            break;
          }
          tmp_range++;
