             SHORTPAIR(hostlen),

             SHORTPAIR(hostoff),

             0,0,

             host, domain);



    /* initial packet length */

    size = 32 + hostlen + domlen;



    /* now keeper of the base64 encoded package size */

    size = Curl_base64_encode((char *)ntlmbuf, size, &base64);



    if(size >0 ) {

      Curl_safefree(*allocuserpwd);

      *allocuserpwd = aprintf("%sAuthorization: NTLM %s\r\n",

                              proxy?"Proxy-":"",

                              base64);

      free(base64);

    }

    else

