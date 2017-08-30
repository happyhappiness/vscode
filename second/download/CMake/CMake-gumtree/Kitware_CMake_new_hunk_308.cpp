  struct TELNET *tn = (struct TELNET *)data->req.protop;



  printsub(data, '<', (unsigned char *)tn->subbuffer, CURL_SB_LEN(tn)+2);

  switch(CURL_SB_GET(tn)) {

    case CURL_TELOPT_TTYPE:

      len = strlen(tn->subopt_ttype) + 4 + 2;

      snprintf((char *)temp, sizeof(temp),

