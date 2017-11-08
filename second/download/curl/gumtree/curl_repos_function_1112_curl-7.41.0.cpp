void curl_mark_sclose(curl_socket_t sockfd, int line, const char *source)
{
  const char *fmt = (sizeof(curl_socket_t) == sizeof(int)) ?
                    "FD %s:%d sclose(%d)\n" :
                    (sizeof(curl_socket_t) == sizeof(long)) ?
                    "FD %s:%d sclose(%ld)\n" :
                    "FD %s:%d sclose(%zd)\n" ;

  if(source)
    curl_memlog(fmt, source, line, sockfd);
}