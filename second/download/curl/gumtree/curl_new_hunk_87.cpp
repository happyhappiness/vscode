                if((CURLE_OK ==
                    curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &stringp))
                   && stringp)
                  fputs(stringp, stream);
                break;
              default:
                /* -Wunreachable-code wrongly complains on this */
                break;
              }
              break;
            }
          }
          ptr=end+1; /* pass the end */
