              case VAR_REDIRECT_URL:
                if((CURLE_OK ==
                    curl_easy_getinfo(curl, CURLINFO_REDIRECT_URL, &stringp))
                   && stringp)
                  fputs(stringp, stream);
                break;
              case VAR_SSL_VERIFY_RESULT:
                if(CURLE_OK ==
                   curl_easy_getinfo(curl, CURLINFO_SSL_VERIFYRESULT, &longinfo))
                  fprintf(stream, "%ld", longinfo);
                break;
              default:
                break;
              }
              break;
            }
          }
