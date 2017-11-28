unsigned char
ClassCBucket::hostPosition (DelaySpec &rate, unsigned char const host)
{
    if (individualAllocated (host))
        return findHostMapPosition(host);

    assert (!individualUsed (findHostMapPosition(host)));

    unsigned char result = findHostMapPosition(host);

    initHostIndex (rate, result, host);

    return result;
}