Curl_addrinfo *Curl_addrinfo_copy(const void *org, int port)
{
  const struct hostent *orig = org;

  return Curl_he2ai(orig, port);
}