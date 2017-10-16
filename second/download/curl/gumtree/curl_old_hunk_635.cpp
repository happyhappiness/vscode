              sep = (char *)type + strlen(major)+strlen(minor)+1;

              /* there's a semicolon following - we check if it is a filename
                 specified and if not we simply assume that it is text that
                 the user wants included in the type and include that too up
                 to the next zero or semicolon. */
              if((*sep==';') && !checkprefix(";filename=", sep)) {
                sep2 = strchr(sep+1, ';');
                if(sep2)
                  sep = sep2;
                else
                  sep = sep + strlen(sep); /* point to end of string */
              }

              if(*sep) {
                *sep = '\0'; /* zero terminate type string */

                ptr = sep+1;
              }
              else
                ptr = NULL; /* end */
            }
            else if(checkprefix("filename=", ptr)) {
              filename = &ptr[9];
              ptr = strchr(filename, FORM_TYPE_SEPARATOR);
              if(!ptr) {
                ptr = strchr(filename, FORM_FILE_SEPARATOR);
              }
              if(ptr) {
                *ptr = '\0'; /* zero terminate */
                ptr++;
              }
            }
            else
              /* confusion, bail out of loop */
              break;
          }
          /* find the following comma */
          if(ptr)
            sep = strchr(ptr, FORM_FILE_SEPARATOR);
          else
            sep = NULL;
        }
        else {
          sep = strchr(contp, FORM_FILE_SEPARATOR);
        }
        if(sep) {
          /* the next file name starts here */
          *sep = '\0';
          sep++;
        }
        /* if type == NULL curl_formadd takes care of the problem */

        if(!AddMultiFiles(contp, type, filename, &multi_start,
                          &multi_current)) {
          warnf(config, "Error building form post!\n");
          Curl_safefree(contents);
