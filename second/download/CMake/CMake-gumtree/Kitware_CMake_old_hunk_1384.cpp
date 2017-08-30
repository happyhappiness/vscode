 * returns a pointer to the malloc()ed copy. You need to call free() on the

 * returned buffer when you're done with it.

 */

Curl_addrinfo *Curl_addrinfo_copy(void *org, int port)

{

  struct hostent *orig = org;



  return Curl_he2ai(orig, port);

}

#endif /* CURLRES_ADDRINFO_COPY */

