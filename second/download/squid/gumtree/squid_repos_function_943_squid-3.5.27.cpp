void
ClientInfo::setWriteLimiter(const int aWriteSpeedLimit, const double anInitialBurst, const double aHighWatermark)
{
    debugs(77,5, HERE << "Write limits for " << (const char*)hash.key <<
           " speed=" << aWriteSpeedLimit << " burst=" << anInitialBurst <<
           " highwatermark=" << aHighWatermark);

    // set or possibly update traffic shaping parameters
    writeLimitingActive = true;
    writeSpeedLimit = aWriteSpeedLimit;
    bucketSizeLimit = aHighWatermark;

    // but some members should only be set once for a newly activated bucket
    if (firstTimeConnection) {
        firstTimeConnection = false;

        assert(!selectWaiting);
        assert(!quotaQueue);
        quotaQueue = new CommQuotaQueue(this);

        bucketSize = anInitialBurst;
        prevTime = current_dtime;
    }
}