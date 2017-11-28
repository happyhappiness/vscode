static int
fdIsDns(int fd)
{
    if (fd == DnsSocketA)
        return 1;

    if (fd == DnsSocketB)
        return 1;

    return 0;
}