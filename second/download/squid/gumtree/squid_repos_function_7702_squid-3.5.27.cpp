inline char *
inet_ntop(int af, const void *src, char *dst, size_t size)
{
    return (char*)InetNtopA(af, const_cast<void*>(src), dst, size);
}