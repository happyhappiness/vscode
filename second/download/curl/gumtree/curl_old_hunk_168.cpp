      else {
        /* this is meant as a variable to output */
        char *end;
        char keepit;
        int i;
        if(('{' == ptr[1]) && (end=strchr(ptr, '}'))) {
          ptr+=2; /* pass the % and the { */
          keepit=*end;
          *end=0; /* zero terminate */
          for(i=0; replacements[i].name; i++) {
            if(curl_strequal(ptr, replacements[i].name)) {
              switch(replacements[i].id) {
              case VAR_EFFECTIVE_URL:
                if((CURLE_OK ==
                    curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &stringp))
                   && stringp)
                  fputs(stringp, stream);
