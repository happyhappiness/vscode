                break;
              case VAR_SPEED_UPLOAD:
                if(CURLE_OK ==
                   curl_easy_getinfo(curl, CURLINFO_SPEED_UPLOAD, &doubleinfo))
                  fprintf(stream, "%.3f", doubleinfo);
                break;
              case VAR_CONTENT_TYPE:
                if(CURLE_OK ==
                   curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &stringp))
                   fputs(stringp, stream);
               break;
              default:
                break;
              }
              break;
            }
          }
