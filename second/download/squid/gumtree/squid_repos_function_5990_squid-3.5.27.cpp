int64_t
HierarchyLogEntry::totalResponseTime()
{
    // This should not really happen, but there may be rare code
    // paths that lead to FwdState discarded (or transaction logged)
    // without (or before) a stopPeerClock() call.
    if (firstConnStart_.tv_sec && totalResponseTime_ < 0)
        stopPeerClock(false);

    return totalResponseTime_;
}