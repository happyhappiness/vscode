                    SHORTPAIR(hostlen),

                    SHORTPAIR(hostlen),

                    SHORTPAIR(hostoff),

                    0x0, 0x0,



                    0x0, 0x0,

                    0x0, 0x0,

                    0x0, 0x0,

                    0x0, 0x0,



                    LONGQUARTET(ntlm->flags));

    DEBUG_OUT(assert(size==64));



    DEBUG_OUT(assert(size == lmrespoff));

    /* We append the binary hashes */

    if(size < (sizeof(ntlmbuf) - 0x18)) {

      memcpy(&ntlmbuf[size], lmresp, 0x18);

      size += 0x18;

    }



    DEBUG_OUT({

        fprintf(stderr, "**** TYPE3 header lmresp=");

        print_hex(stderr, (char *)&ntlmbuf[lmrespoff], 0x18);

    });



#if USE_NTRESPONSES

    if(size < (sizeof(ntlmbuf) - 0x18)) {

      DEBUG_OUT(assert(size == ntrespoff));

      memcpy(&ntlmbuf[size], ntresp, 0x18);

      size += 0x18;

    }



    DEBUG_OUT({

        fprintf(stderr, "\n                  ntresp=");

        print_hex(stderr, (char *)&ntlmbuf[ntrespoff], 0x18);

    });



#endif



    DEBUG_OUT({

        fprintf(stderr, "\n                  flags=0x%02.2x%02.2x%02.2x%02.2x 0x%08.8x ",

                LONGQUARTET(ntlm->flags), ntlm->flags);

        print_flags(stderr, ntlm->flags);

        fprintf(stderr, "\n****\n");

    });





    /* Make sure that the domain, user and host strings fit in the target

       buffer before we copy them there. */

    if(size + userlen + domlen + hostlen >= sizeof(ntlmbuf)) {

      failf(conn->data, "user + domain + host name too big");

      return CURLE_OUT_OF_MEMORY;

    }



    curlassert(size == domoff);

    memcpy(&ntlmbuf[size], domain, domlen);

    size += domlen;



    curlassert(size == useroff);

    memcpy(&ntlmbuf[size], user, userlen);

    size += userlen;



    curlassert(size == hostoff);

    memcpy(&ntlmbuf[size], host, hostlen);

    size += hostlen;



#ifdef CURL_DOES_CONVERSIONS

    /* convert domain, user, and host to ASCII but leave the rest as-is */

    if(CURLE_OK != Curl_convert_to_network(conn->data, 

                                           (char *)&ntlmbuf[domoff],

                                           size-domoff)) {

      return CURLE_CONV_FAILED;

    }

#endif /* CURL_DOES_CONVERSIONS */



#endif



    /* convert the binary blob into base64 */

    size = Curl_base64_encode(NULL, (char *)ntlmbuf, size, &base64);



    if(size >0 ) {

      Curl_safefree(*allocuserpwd);

      *allocuserpwd = aprintf("%sAuthorization: NTLM %s\r\n",

                              proxy?"Proxy-":"",

                              base64);

      DEBUG_OUT(fprintf(stderr, "**** %s\n ", *allocuserpwd));

      free(base64);

    }

    else

