static char *inet_ntop4 (const u_char *src, char *dst, size_t size)
{
#if defined(HAVE_INET_NTOA_R_2_ARGS)
  const char *ptr;
  curlassert(size >= 16);
  ptr = inet_ntoa_r(*(struct in_addr*)src, dst);
  return (char *)memmove(dst, ptr, strlen(ptr)+1);

#elif defined(HAVE_INET_NTOA_R)
  return inet_ntoa_r(*(struct in_addr*)src, dst, size);

#else
  const char *addr = inet_ntoa(*(struct in_addr*)src);

  if (strlen(addr) >= size)
  {
    SET_ERRNO(ENOSPC);
    return (NULL);
  }
  return strcpy(dst, addr);
#endif
}