void
HierarchyLogEntry::stopPeerClock(const bool force)
{
    debugs(46, 5, "First connection started: " << firstConnStart_.tv_sec << "." <<
           std::setfill('0') << std::setw(6) << firstConnStart_.tv_usec <<
           ", current total response time value: " << totalResponseTime_ <<
           (force ? ", force fixing" : ""));
    if (!force && totalResponseTime_ >= 0)
        return;

    totalResponseTime_ = firstConnStart_.tv_sec ? tvSubMsec(firstConnStart_, current_time) : -1;
}