static
int my_trace(CURL *handle, curl_infotype type,
             unsigned char *data, size_t size,
             void *userp)
{
  struct Configurable *config = (struct Configurable *)userp;
  FILE *output=config->errors;
  const char *text;
  struct timeval tv;
  struct tm *now;
  char timebuf[15];

  (void)handle; /* prevent compiler warning */

  tv = curlx_tvnow();
  now = localtime(&tv.tv_sec);  /* not multithread safe but we don't care */
  if(config->tracetime)
    snprintf(timebuf, sizeof(timebuf), "%02d:%02d:%02d.%02d ",
             now->tm_hour, now->tm_min, now->tm_sec,
             tv.tv_usec/10000);
  else
    timebuf[0]=0;

  if(!config->trace_stream) {
    /* open for append */
    if(curlx_strequal("-", config->trace_dump))
      config->trace_stream = stdout;
    else if(curlx_strequal("%", config->trace_dump))
      /* Ok, this is somewhat hackish but we do it undocumented for now */
      config->trace_stream = stderr;
    else {
      config->trace_stream = fopen(config->trace_dump, "w");
      config->trace_fopened = TRUE;
    }
  }

  if(config->trace_stream)
    output = config->trace_stream;

  if(config->tracetype == TRACE_PLAIN) {
    /*
     * This is the trace look that is similar to what libcurl makes on its
     * own.
     */
    static const char * const s_infotype[] = {
      "*", "<", ">"
    };
    size_t i;
    size_t st=0;
    static bool newl = FALSE;

    switch(type) {
    case CURLINFO_HEADER_OUT:
      for(i=0; i<size-1; i++) {
        if(data[i] == '\n') { /* LF */
          if(!newl) {
            fprintf(config->trace_stream, "%s%s ",
                    timebuf, s_infotype[type]);
          }
          fwrite(data+st, i-st+1, 1, config->trace_stream);
          st = i+1;
          newl = FALSE;
        }
      }
      if(!newl)
        fprintf(config->trace_stream, "%s%s ", timebuf, s_infotype[type]);
      fwrite(data+st, i-st+1, 1, config->trace_stream);
      break;
    case CURLINFO_TEXT:
    case CURLINFO_HEADER_IN:
      if(!newl)
        fprintf(config->trace_stream, "%s%s ", timebuf, s_infotype[type]);
      fwrite(data, size, 1, config->trace_stream);
      break;
    default: /* nada */
      newl = FALSE;
      break;
    }

    newl = (size && (data[size-1] != '\n'));

    return 0;
  }


  switch (type) {
  case CURLINFO_TEXT:
    fprintf(output, "%s== Info: %s", timebuf, data);
  default: /* in case a new one is introduced to shock us */
    return 0;

  case CURLINFO_HEADER_OUT:
    text = "=> Send header";
    break;
  case CURLINFO_DATA_OUT:
    text = "=> Send data";
    break;
  case CURLINFO_HEADER_IN:
    text = "<= Recv header";
    break;
  case CURLINFO_DATA_IN:
    text = "<= Recv data";
    break;
  case CURLINFO_SSL_DATA_IN:
    text = "<= Recv SSL data";
    break;
  case CURLINFO_SSL_DATA_OUT:
    text = "<= Send SSL data";
    break;
  }

  dump(timebuf, text, output, data, size, config->tracetype);
  return 0;
}