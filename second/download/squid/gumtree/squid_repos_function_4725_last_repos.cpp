static int
memcasecmp(const char *b1, const char *b2, SBuf::size_type len)
{
    int rv=0;
    while (len > 0) {
        rv = tolower(*b1)-tolower(*b2);
        if (rv != 0)
            return rv;
        ++b1;
        ++b2;
        --len;
    }
    return rv;
}