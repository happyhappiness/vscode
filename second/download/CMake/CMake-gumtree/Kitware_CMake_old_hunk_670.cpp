    if(res)

      return res;



    Curl_safefree(*allocuserpwd);

    *allocuserpwd = aprintf("%sAuthorization: %s\r\n",

                            proxy ? "Proxy-" : "",

                            conn->response_header);

