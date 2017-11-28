void
HierarchyLogEntry::startPeerClock()
{
    if (!firstConnStart_.tv_sec)
        firstConnStart_ = current_time;
}