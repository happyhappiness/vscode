{
    infof(conn->data, "getaddrinfo() failed for %s:%d; %s\n",
          hostname, port, Curl_strerror(conn, SOCKERRNO));
    return NULL;
  }