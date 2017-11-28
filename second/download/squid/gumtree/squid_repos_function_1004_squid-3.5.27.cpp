inline bool logTypeIsATcpHit(LogTags code)
{
    return
        (code == LOG_TCP_HIT) ||
        (code == LOG_TCP_IMS_HIT) ||
        (code == LOG_TCP_INM_HIT) ||
        (code == LOG_TCP_REFRESH_FAIL_OLD) ||
        (code == LOG_TCP_REFRESH_UNMODIFIED) ||
        (code == LOG_TCP_NEGATIVE_HIT) ||
        (code == LOG_TCP_MEM_HIT) ||
        (code == LOG_TCP_OFFLINE_HIT);
}