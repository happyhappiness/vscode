unsigned long long htonll(unsigned long long n) {
#if BYTE_ORDER == BIG_ENDIAN
  return n;
#else
  return (((unsigned long long)htonl(n)) << 32) + htonl(n >> 32);
#endif
}