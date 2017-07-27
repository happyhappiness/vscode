*allocuserpwd = aprintf("%sAuthorization: %s\r\n",
                            proxy ? "Proxy-" : "",
                            conn->response_header);