void Adaptation::Icap::Xaction::maybeLog()
{
    if (IcapLogfileStatus == LOG_ENABLE) {
        finalizeLogInfo();
        icapLogLog(alep);
    }
}