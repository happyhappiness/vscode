*userp = aprintf("%sAuthorization: Basic %s\r\n",
                   proxy ? "Proxy-" : "",
                   authorization)