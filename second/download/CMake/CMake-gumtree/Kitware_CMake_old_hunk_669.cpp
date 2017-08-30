    if(res)

      return res;



    Curl_safefree(*allocuserpwd);

    *allocuserpwd = aprintf("%sAuthorization: %s\r\n",

                            proxy ? "Proxy-" : "",

                            conn->response_header);

    DEBUG_OUT(fprintf(stderr, "**** Header %s\n ", *allocuserpwd));

    Curl_safefree(conn->response_header);

    conn->response_header = NULL;

    break;

  case NTLMSTATE_TYPE2:

