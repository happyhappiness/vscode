                break;
              case VAR_SPEED_UPLOAD:
                if(CURLE_OK ==
                   curl_easy_getinfo(curl, CURLINFO_SPEED_UPLOAD, &doubleinfo))
                  fprintf(stream, "%.3f", doubleinfo);
                break;
              default:
                break;
              }
              break;
            }
          }
