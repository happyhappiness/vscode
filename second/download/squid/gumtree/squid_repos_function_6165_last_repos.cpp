void
HierarchyLogEntry::stopPeerClock(const bool force)
{
    debugs(46, 5, "First connection started: " << firstConnStart_.tv_sec << "." <<
           std::setfill('0') << std::setw(6) << firstConnStart_.tv_usec <<
           ", current total response time value: " << (totalResponseTime_.tv_sec * 1000 +  totalResponseTime_.tv_usec/1000) <<
           (force ? ", force fixing" : ""));
    if (!force && totalResponseTime_.tv_sec != -1)
        return;

    if (firstConnStart_.tv_sec)
        tvSub(totalResponseTime_, firstConnStart_, current_time);
}