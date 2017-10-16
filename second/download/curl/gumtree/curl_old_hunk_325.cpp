              case VAR_REDIRECT_URL:
                if((CURLE_OK ==
                    curl_easy_getinfo(curl, CURLINFO_REDIRECT_URL, &stringp))
                   && stringp)
                  fputs(stringp, stream);
                break;
              default:
                break;
              }
              break;
            }
          }
