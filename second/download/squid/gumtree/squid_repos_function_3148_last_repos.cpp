bool
HttpHdrRange::offsetLimitExceeded(const int64_t limit) const
{
    if (limit == 0)
        /* 0 == disabled */
        return true;

    if (-1 == limit)
        /* 'none' == forced */
        return false;

    if (firstOffset() == -1)
        /* tail request */
        return true;

    if (limit >= firstOffset())
        /* below the limit */
        return false;

    return true;
}