CURLcode Curl_addrinfo6_callback(void *arg, /* "struct connectdata *" */
                                 int status,
                                 struct addrinfo *ai)
{
  return addrinfo_callback(arg, status, ai);
}