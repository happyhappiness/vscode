SBuf &
SBuf::append(const char * S, size_type Ssize)
{
    const Locker blobKeeper(this, S);
    if (S == NULL)
        return *this;
    if (Ssize == SBuf::npos)
        Ssize = strlen(S);
    debugs(24, 7, "from c-string to id " << id);
    // coverity[access_dbuff_in_call]
    return lowAppend(S, Ssize);
}