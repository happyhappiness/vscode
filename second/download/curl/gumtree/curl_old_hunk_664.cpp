            if(checkprefix("type=", ptr)) {
              /* set type pointer */
              type = &ptr[5];

              /* verify that this is a fine type specifier */
              if(2 != sscanf(type, "%127[^/]/%127[^;,\n]",
                             major, minor)) {
                warnf(config, "Illegally formatted content-type field!\n");
                Curl_safefree(contents);
                FreeMultiInfo(&multi_start, &multi_current);
                return 2; /* illegal content-type syntax! */
              }

              /* now point beyond the content-type specifier */
              sep = (char *)type + strlen(major)+strlen(minor)+1;

              /* there's a semicolon following - we check if it is a filename
                 specified and if not we simply assume that it is text that
                 the user wants included in the type and include that too up
                 to the next zero or semicolon. */
              if(*sep==';') {
