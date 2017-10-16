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
