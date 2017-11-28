int
clientIsRequestBodyValid(int64_t bodyLength)
{
    if (bodyLength >= 0)
        return 1;

    return 0;
}