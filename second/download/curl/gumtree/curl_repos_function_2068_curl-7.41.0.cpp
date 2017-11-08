void
curl_dofreeaddrinfo(struct addrinfo *freethis,
                    int line, const char *source)
{
  (freeaddrinfo)(freethis);
  curl_memlog("ADDR %s:%d freeaddrinfo(%p)\n",
              source, line, (void *)freethis);
}