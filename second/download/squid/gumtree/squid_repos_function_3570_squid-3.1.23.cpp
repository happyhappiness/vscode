bool
HttpHdrRange::offsetLimitExceeded() const
{
    if (NULL == this)
        /* not a range request */
        return false;

    if (Config.rangeOffsetLimit == 0)
        /* disabled */
        return true;

    if (-1 == Config.rangeOffsetLimit)
        /* forced */
        return false;

    if (firstOffset() == -1)
        /* tail request */
        return true;

    if (Config.rangeOffsetLimit >= firstOffset())
        /* below the limit */
        return false;

    return true;
}