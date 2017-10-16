void ourWriteOut(CURL *curl, const char *writeinfo)
{
  FILE *stream = stdout;
  const char *ptr=writeinfo;
  char *stringp;
  long longinfo;
  double doubleinfo;

  while(*ptr) {
    if('%' == *ptr) {
      if('%' == ptr[1]) {
        /* an escaped %-letter */
        fputc('%', stream);
        ptr+=2;
      }
      else {
        /* this is meant as a variable to output */
        char *end;
        char keepit;
        int i;
        if(('{' == ptr[1]) && (end=strchr(ptr, '}'))) {
          bool match = FALSE;
          ptr+=2; /* pass the % and the { */
          keepit=*end;
          *end=0; /* zero terminate */
          for(i=0; replacements[i].name; i++) {
            if(curl_strequal(ptr, replacements[i].name)) {
              match = TRUE;
              switch(replacements[i].id) {
              case VAR_EFFECTIVE_URL:
                if((CURLE_OK ==
                    curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &stringp))
                   && stringp)
                  fputs(stringp, stream);
                break;
              case VAR_HTTP_CODE:
                if(CURLE_OK ==
                   curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &longinfo))
                  fprintf(stream, "%03ld", longinfo);
                break;
              case VAR_HTTP_CODE_PROXY:
                if(CURLE_OK ==
                   curl_easy_getinfo(curl, CURLINFO_HTTP_CONNECTCODE,
                                     &longinfo))
                  fprintf(stream, "%03ld", longinfo);
                break;
              case VAR_HEADER_SIZE:
                if(CURLE_OK ==
                   curl_easy_getinfo(curl, CURLINFO_HEADER_SIZE, &longinfo))
                  fprintf(stream, "%ld", longinfo);
                break;
              case VAR_REQUEST_SIZE:
                if(CURLE_OK ==
                   curl_easy_getinfo(curl, CURLINFO_REQUEST_SIZE, &longinfo))
                  fprintf(stream, "%ld", longinfo);
                break;
              case VAR_NUM_CONNECTS:
                if(CURLE_OK ==
                   curl_easy_getinfo(curl, CURLINFO_NUM_CONNECTS, &longinfo))
                  fprintf(stream, "%ld", longinfo);
                break;
              case VAR_REDIRECT_COUNT:
                if(CURLE_OK ==
                   curl_easy_getinfo(curl, CURLINFO_REDIRECT_COUNT, &longinfo))
                  fprintf(stream, "%ld", longinfo);
                break;
              case VAR_REDIRECT_TIME:
                if(CURLE_OK ==
                   curl_easy_getinfo(curl, CURLINFO_REDIRECT_TIME, &doubleinfo))
                  fprintf(stream, "%.3f", doubleinfo);
                break;
              case VAR_TOTAL_TIME:
                if(CURLE_OK ==
                   curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &doubleinfo))
                  fprintf(stream, "%.3f", doubleinfo);
                break;
              case VAR_NAMELOOKUP_TIME:
                if(CURLE_OK ==
                   curl_easy_getinfo(curl, CURLINFO_NAMELOOKUP_TIME,
                                     &doubleinfo))
                  fprintf(stream, "%.3f", doubleinfo);
                break;
              case VAR_CONNECT_TIME:
                if(CURLE_OK ==
                   curl_easy_getinfo(curl, CURLINFO_CONNECT_TIME, &doubleinfo))
                  fprintf(stream, "%.3f", doubleinfo);
                break;
              case VAR_PRETRANSFER_TIME:
                if(CURLE_OK ==
                   curl_easy_getinfo(curl, CURLINFO_PRETRANSFER_TIME, &doubleinfo))
                  fprintf(stream, "%.3f", doubleinfo);
                break;
              case VAR_STARTTRANSFER_TIME:
                if(CURLE_OK ==
                   curl_easy_getinfo(curl, CURLINFO_STARTTRANSFER_TIME, &doubleinfo))
                  fprintf(stream, "%.3f", doubleinfo);
                break;
              case VAR_SIZE_UPLOAD:
                if(CURLE_OK ==
                   curl_easy_getinfo(curl, CURLINFO_SIZE_UPLOAD, &doubleinfo))
                  fprintf(stream, "%.0f", doubleinfo);
                break;
              case VAR_SIZE_DOWNLOAD:
                if(CURLE_OK ==
                   curl_easy_getinfo(curl, CURLINFO_SIZE_DOWNLOAD, &doubleinfo))
                  fprintf(stream, "%.0f", doubleinfo);
                break;
              case VAR_SPEED_DOWNLOAD:
                if(CURLE_OK ==
                   curl_easy_getinfo(curl, CURLINFO_SPEED_DOWNLOAD, &doubleinfo))
                  fprintf(stream, "%.3f", doubleinfo);
                break;
              case VAR_SPEED_UPLOAD:
                if(CURLE_OK ==
                   curl_easy_getinfo(curl, CURLINFO_SPEED_UPLOAD, &doubleinfo))
                  fprintf(stream, "%.3f", doubleinfo);
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
          if(!match) {
            fprintf(stderr, "curl: unknown --write-out variable: '%s'\n", ptr);
          }
          ptr=end+1; /* pass the end */
          *end = keepit;
        }
        else {
          /* illegal syntax, then just output the characters that are used */
          fputc('%', stream);
          fputc(ptr[1], stream);
          ptr+=2;
        }
      }
    }
    else if('\\' == *ptr) {
      switch(ptr[1]) {
      case 'r':
        fputc('\r', stream);
        break;
      case 'n':
        fputc('\n', stream);
        break;
      case 't':
        fputc('\t', stream);
        break;
      default:
        /* unknown, just output this */
        fputc(*ptr, stream);
        fputc(ptr[1], stream);
        break;
      }
      ptr+=2;
    }
    else {
      fputc(*ptr, stream);
      ptr++;
    }
  }

}