int
fdNFree(void)
{
    return Squid_MaxFD - Number_FD - Opening_FD;
}