int
logTypeIsATcpHit(log_type code)
{
    /* this should be a bitmap for better optimization */

    if (code == LOG_TCP_HIT)
        return 1;

    if (code == LOG_TCP_IMS_HIT)
        return 1;

    if (code == LOG_TCP_REFRESH_FAIL_OLD)
        return 1;

    if (code == LOG_TCP_REFRESH_UNMODIFIED)
        return 1;

    if (code == LOG_TCP_NEGATIVE_HIT)
        return 1;

    if (code == LOG_TCP_MEM_HIT)
        return 1;

    if (code == LOG_TCP_OFFLINE_HIT)
        return 1;

    return 0;
}