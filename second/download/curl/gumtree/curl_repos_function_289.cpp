CURLcode Curl_addrinfo4_callback(void *arg, /* "struct connectdata *" */
                                 int status,
                                 struct hostent *hostent)
{
  return addrinfo_callback(arg, status, hostent);
}