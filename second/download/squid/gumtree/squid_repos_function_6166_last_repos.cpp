void
HierarchyLogEntry::totalResponseTime(struct timeval &responseTime)
{
    // This should not really happen, but there may be rare code
    // paths that lead to FwdState discarded (or transaction logged)
    // without (or before) a stopPeerClock() call.
    if (firstConnStart_.tv_sec && totalResponseTime_.tv_sec == -1)
        stopPeerClock(false);

    responseTime = totalResponseTime_;
}