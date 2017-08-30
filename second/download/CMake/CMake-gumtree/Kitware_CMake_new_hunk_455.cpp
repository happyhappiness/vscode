

  free(*userp);

  *userp = aprintf("%sAuthorization: Basic %s\r\n",

                   proxy ? "Proxy-" : "",

                   authorization);

  free(authorization);

  if(!*userp)

