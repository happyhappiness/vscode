inline char *
inet_ntop(int af, const void *src, char *dst, size_t size)
{
#if HAVE_DECL_INETNTOPA
    return (char*)InetNtopA(af, const_cast<void*>(src), dst, size);
#else
    return ::inet_ntop(af, src, dst, size);
#endif
}