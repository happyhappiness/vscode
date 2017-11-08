void
curl_dofreeaddrinfo(struct addrinfo *freethis,
                    int line, const char *source)
{
#ifdef USE_LWIPSOCK
  lwip_freeaddrinfo(freethis);
#else
  (freeaddrinfo)(freethis);
#endif
  curl_memlog("ADDR %s:%d freeaddrinfo(%p)\n",
              source, line, (void *)freethis);
}