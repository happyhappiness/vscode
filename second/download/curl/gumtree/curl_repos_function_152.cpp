void WriteOut(struct UrlData *data)
{
  FILE *stream = stdout;
  char *ptr=data->writeinfo;
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
          ptr+=2; /* pass the % and the { */
          keepit=*end;
          *end=0; /* zero terminate */
          for(i=0; replacements[i].name; i++) {
            if(strequal(ptr, replacements[i].name)) {
              switch(replacements[i].id) {
              case VAR_EFFECTIVE_URL:
                fprintf(stream, "%s", data->url?data->url:"");
                break;
              case VAR_HTTP_CODE:
                fprintf(stream, "%03d", data->progress.httpcode);
                break;
              case VAR_TOTAL_TIME:
                fprintf(stream, "%.3f", data->progress.timespent);
                break;
              case VAR_NAMELOOKUP_TIME:
                fprintf(stream, "%.3f", tvdiff(data->progress.t_nslookup,
                                               data->progress.start));
                break;
              case VAR_CONNECT_TIME:
                fprintf(stream, "%.3f", tvdiff(data->progress.t_connect,
                                               data->progress.start));
                break;
              case VAR_PRETRANSFER_TIME:
                fprintf(stream, "%.3f", tvdiff(data->progress.t_pretransfer,
                                               data->progress.start));
                break;
              case VAR_SIZE_UPLOAD:
                fprintf(stream, "%.0f", data->progress.uploaded);
                break;
              case VAR_SIZE_DOWNLOAD:
                fprintf(stream, "%.0f", data->progress.downloaded);
                break;
              case VAR_SPEED_DOWNLOAD:
                fprintf(stream, "%.2f", data->progress.dlspeed);
                break;
              case VAR_SPEED_UPLOAD:
                fprintf(stream, "%.2f", data->progress.ulspeed);
                break;
              }
              break;
            }
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