    if(res)
      return res;

    free(*allocuserpwd);
    *allocuserpwd = aprintf("%sAuthorization: %s\r\n",
                            proxy ? "Proxy-" : "",
                            conn->response_header);
