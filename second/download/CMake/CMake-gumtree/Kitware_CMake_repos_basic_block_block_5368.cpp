result = Curl_client_write(conn, CLIENTWRITE_BODY,
                                   (char *)msg + off + sizeof(unsigned int),
                                   len)