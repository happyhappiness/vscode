int test(char *URL)
{
  CURLM* multi;
  sslctxparm p;

  int i = 0;
  CURLMsg *msg;

  if(arg2) {
    portnum = atoi(arg2);
  }

  curl_global_init(CURL_GLOBAL_ALL);

  p.curl = curl_easy_init();

  p.accessinfoURL = (unsigned char *) strdup(URL);
  p.accesstype = OBJ_obj2nid(OBJ_txt2obj("AD_DVCS",0)) ;

  curl_easy_setopt(p.curl, CURLOPT_URL, p.accessinfoURL);

  curl_easy_setopt(p.curl, CURLOPT_SSL_CTX_FUNCTION, sslctxfun)  ;
  curl_easy_setopt(p.curl, CURLOPT_SSL_CTX_DATA, &p);

  curl_easy_setopt(p.curl, CURLOPT_SSL_VERIFYPEER, FALSE);
  curl_easy_setopt(p.curl, CURLOPT_SSL_VERIFYHOST, 1);

  fprintf(stderr, "Going to perform %s\n", (char *)p.accessinfoURL);

  {
    CURLMcode res;
    int running;
    char done=FALSE;

    multi = curl_multi_init();

    res = curl_multi_add_handle(multi, p.curl);

    while(!done) {
      fd_set rd, wr, exc;
      int max_fd;
      struct timeval interval;

      interval.tv_sec = 1;
      interval.tv_usec = 0;

      while (res == CURLM_CALL_MULTI_PERFORM) {
        res = curl_multi_perform(multi, &running);
        fprintf(stderr, "running=%d res=%d\n",running,res);
        if (running <= 0) {
          done = TRUE;
          break;
        }
      }
      if(done)
        break;

      if (res != CURLM_OK) {
        fprintf(stderr, "not okay???\n");
        i = 80;
        break;
      }

      FD_ZERO(&rd);
      FD_ZERO(&wr);
      FD_ZERO(&exc);
      max_fd = 0;

      if (curl_multi_fdset(multi, &rd, &wr, &exc, &max_fd) != CURLM_OK) {
        fprintf(stderr, "unexpected failured of fdset.\n");
        i = 89;
        break;
      }

      if (select(max_fd+1, &rd, &wr, &exc, &interval) == -1) {
        fprintf(stderr, "bad select??\n");
        i =95;
        break;
      }

      res = CURLM_CALL_MULTI_PERFORM;
    }
    msg = curl_multi_info_read(multi, &running);
    /* this should now contain a result code from the easy handle, get it */
    if(msg)
      i = msg->data.result;
  }

  fprintf(stderr, "all done\n");

  curl_multi_remove_handle(multi, p.curl);
  curl_easy_cleanup(p.curl);
  curl_multi_cleanup(multi);

  curl_global_cleanup();
  free(p.accessinfoURL);

  return i;
}