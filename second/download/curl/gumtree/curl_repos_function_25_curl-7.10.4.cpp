size_t url_fread(void *ptr, size_t size, size_t nmemb, URL_FILE *file)
{
  fd_set fdread;
  fd_set fdwrite;
  fd_set fdexcep;
  int maxfd;
  struct timeval timeout;
  int rc;
  int still_running = 0;

  if(!file->bytes) { /* no data available at this point */

    file->readptr = file->buffer; /* reset read pointer */

    if(CURLM_CALL_MULTI_PERFORM == file->m) {
      while(CURLM_CALL_MULTI_PERFORM ==
            curl_multi_perform(multi_handle, &still_running)) {
        if(file->bytes) {
          printf("(fread) WOAH! THis happened!\n");
          break;        
        }
      }
      if(!still_running) {
        printf("DONE RUNNING AROUND!\n");
        return 0;
      }
    }

    do {

      FD_ZERO(&fdread);
      FD_ZERO(&fdwrite);
      FD_ZERO(&fdexcep);
  
      /* set a suitable timeout to fail on */
      timeout.tv_sec = 500; /* 5 minutes */
      timeout.tv_usec = 0;

      /* get file descriptors from the transfers */
      curl_multi_fdset(multi_handle, &fdread, &fdwrite, &fdexcep, &maxfd);

      rc = select(maxfd+1, &fdread, &fdwrite, &fdexcep, &timeout);

      switch(rc) {
      case -1:
        /* select error */
        break;
      case 0:
        break;
      default:
        /* timeout or readable/writable sockets */
        printf("select() returned %d!\n", rc);
        do {
          file->m = curl_multi_perform(multi_handle, &still_running);
          
          if(file->bytes)
            /* we have received data, return that now */
            break;
          
        } while(CURLM_CALL_MULTI_PERFORM == file->m);

        
        if(!still_running)
          printf("DONE RUNNING AROUND!\n");
        
        break;
      }
    } while(still_running && (file->bytes <= 0));
  }
  else
    printf("(fread) Skip network read\n");

  if(file->bytes) {
    /* data already available, return that */
    int want = size * nmemb;

    if(file->bytes < want)
      want = file->bytes;

    memcpy(ptr, file->readptr, want);
    file->readptr += want;
    file->bytes -= want;

    printf("(fread) return %d bytes\n", want);

    return want;
  }
  return 0; /* no data available to return */
}