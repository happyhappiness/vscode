CURLcode
curl_easy_getinfo_ccsid(CURL * curl, CURLINFO info, ...)

{
  va_list arg;
  void * paramp;
  CURLcode ret;
  unsigned int ccsid;
  char * * cpp;
  struct Curl_easy * data;
  struct curl_slist * * slp;
  struct curl_certinfo * cipf;
  struct curl_certinfo * cipt;

  /* WARNING: unlike curl_easy_get_info(), the strings returned by this
     procedure have to be free'ed. */

  data = (struct Curl_easy *) curl;
  va_start(arg, info);
  paramp = va_arg(arg, void *);
  ret = Curl_getinfo(data, info, paramp);

  if(ret == CURLE_OK)
    switch ((int) info & CURLINFO_TYPEMASK) {

    case CURLINFO_STRING:
      ccsid = va_arg(arg, unsigned int);
      cpp = (char * *) paramp;

      if(*cpp) {
        *cpp = dynconvert(ccsid, *cpp, -1, ASCII_CCSID);

        if(!*cpp)
          ret = CURLE_OUT_OF_MEMORY;
      }

      break;

    case CURLINFO_SLIST:
      ccsid = va_arg(arg, unsigned int);
      switch (info) {
      case CURLINFO_CERTINFO:
        cipf = *(struct curl_certinfo * *) paramp;
        if(cipf) {
          if(!(cipt = (struct curl_certinfo *) malloc(sizeof *cipt)))
            ret = CURLE_OUT_OF_MEMORY;
          else {
            cipt->certinfo = (struct curl_slist * *)
                             calloc(cipf->num_of_certs +
                                    1, sizeof(struct curl_slist *));
            if(!cipt->certinfo)
              ret = CURLE_OUT_OF_MEMORY;
            else {
              int i;

              cipt->num_of_certs = cipf->num_of_certs;
              for(i = 0; i < cipf->num_of_certs; i++)
                if(cipf->certinfo[i])
                  if(!(cipt->certinfo[i] = slist_convert(ccsid,
                                                          cipf->certinfo[i],
                                                          ASCII_CCSID))) {
                    ret = CURLE_OUT_OF_MEMORY;
                    break;
                  }
              }
            }

          if(ret != CURLE_OK) {
            curl_certinfo_free_all(cipt);
            cipt = (struct curl_certinfo *) NULL;
          }

          *(struct curl_certinfo * *) paramp = cipt;
        }

        break;

      case CURLINFO_TLS_SESSION:
      case CURLINFO_TLS_SSL_PTR:
      case CURLINFO_SOCKET:
        break;

      default:
        slp = (struct curl_slist * *) paramp;
        if(*slp)
          if(!(*slp = slist_convert(ccsid, *slp, ASCII_CCSID)))
            ret = CURLE_OUT_OF_MEMORY;
        break;
      }
    }

  va_end(arg);
  return ret;
}