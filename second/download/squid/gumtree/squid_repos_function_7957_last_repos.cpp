inline char *
inet_pton(int af, const void *src, char *dst)
{
#if HAVE_DECL_INETPTONA
    return (char*)InetPtonA(af, const_cast<void*>(src), dst);
#else
    return ::inet_pton(af, src, dst);
#endif
}