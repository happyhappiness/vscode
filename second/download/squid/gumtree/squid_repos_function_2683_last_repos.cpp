bool
LogTags::isTcpHit() const
{
    return
        (oldType == LOG_TCP_HIT) ||
        (oldType == LOG_TCP_IMS_HIT) ||
        (oldType == LOG_TCP_INM_HIT) ||
        (oldType == LOG_TCP_REFRESH_FAIL_OLD) ||
        (oldType == LOG_TCP_REFRESH_UNMODIFIED) ||
        (oldType == LOG_TCP_NEGATIVE_HIT) ||
        (oldType == LOG_TCP_MEM_HIT) ||
        (oldType == LOG_TCP_OFFLINE_HIT);
}