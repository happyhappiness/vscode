int
fdUsageHigh(void)
{
    int nrfree = fdNFree();

    if (nrfree < (RESERVED_FD << 1))
        return 1;

    if (nrfree < (Number_FD >> 2))
        return 1;

    return 0;
}