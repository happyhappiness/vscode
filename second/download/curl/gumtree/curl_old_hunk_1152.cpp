      }
      else {
        /* this is meant as a variable to output */
        char *end;
        char keepit;
        int i;
        if(('{' == ptr[1]) && ((end = strchr(ptr, '}')) != NULL)) {
          bool match = FALSE;
          ptr += 2; /* pass the % and the { */
          keepit = *end;
          *end = 0; /* zero terminate */
          for(i = 0; replacements[i].name; i++) {
            if(curl_strequal(ptr, replacements[i].name)) {
              match = TRUE;
              switch(replacements[i].id) {
