                break;
              case VAR_CONTENT_TYPE:
                if((CURLE_OK ==
                    curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &stringp))
                   && stringp)
                  fputs(stringp, stream);
                break;
              case VAR_FTP_ENTRY_PATH:
                if((CURLE_OK ==
                    curl_easy_getinfo(curl, CURLINFO_FTP_ENTRY_PATH, &stringp))
                   && stringp)
                  fputs(stringp, stream);
                break;
              default:
                break;
              }
              break;
            }
          }
          if(!match) {
            fprintf(stderr, "curl: unknown --write-out variable: '%s'\n", ptr);
          }
          ptr=end+1; /* pass the end */
          *end = keepit;
        }
        else {
          /* illegal syntax, then just output the characters that are used */
