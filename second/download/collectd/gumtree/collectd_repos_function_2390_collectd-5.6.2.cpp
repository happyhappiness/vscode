unsigned long long ntohll(unsigned long long n) {
#if BYTE_ORDER == BIG_ENDIAN
  return (n);
#else
  return (((unsigned long long)ntohl(n)) << 32) + ntohl(n >> 32);
#endif
}