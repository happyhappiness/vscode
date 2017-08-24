{
    free(pp->sendthis);
    pp->sendthis=NULL;
    pp->sendleft = pp->sendsize = 0;
    pp->response = Curl_tvnow();
  }