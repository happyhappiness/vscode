    if(res)

      return res;



    free(*allocuserpwd);

    *allocuserpwd = aprintf("%sAuthorization: %s\r\n",

                            proxy ? "Proxy-" : "",

                            conn->response_header);

    DEBUG_OUT(fprintf(stderr, "**** Header %s\n ", *allocuserpwd));

    free(conn->response_header);

    conn->response_header = NULL;

    break;

  case NTLMSTATE_TYPE2:

