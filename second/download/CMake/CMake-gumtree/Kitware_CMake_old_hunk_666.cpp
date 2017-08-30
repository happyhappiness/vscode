  case NTLMSTATE_TYPE1:

  default: /* for the weird cases we (re)start here */

    /* Create a type-1 message */

    error = Curl_ntlm_create_type1_message(userp, passwdp, ntlm, &base64,

                                           &len);

    if(error)

      return error;



    if(base64) {

      Curl_safefree(*allocuserpwd);

      *allocuserpwd = aprintf("%sAuthorization: NTLM %s\r\n",

                              proxy ? "Proxy-" : "",

                              base64);

      free(base64);

      if(!*allocuserpwd)

        return CURLE_OUT_OF_MEMORY;

      DEBUG_OUT(fprintf(stderr, "**** Header %s\n ", *allocuserpwd));

    }

    break;



  case NTLMSTATE_TYPE2:

    /* We already received the type-2 message, create a type-3 message */

    error = Curl_ntlm_create_type3_message(conn->data, userp, passwdp,

                                           ntlm, &base64, &len);

    if(error)

      return error;



    if(base64) {

      Curl_safefree(*allocuserpwd);

      *allocuserpwd = aprintf("%sAuthorization: NTLM %s\r\n",

                              proxy ? "Proxy-" : "",

                              base64);

      free(base64);

      if(!*allocuserpwd)

        return CURLE_OUT_OF_MEMORY;

      DEBUG_OUT(fprintf(stderr, "**** %s\n ", *allocuserpwd));



      ntlm->state = NTLMSTATE_TYPE3; /* we send a type-3 */

