void
Adaptation::Icap::History::processingTime(timeval &total) const
{
    currentTime(total);
    tvAssignAdd(total, pastTime);
    debugs(93,7, HERE << " current total: " << tvToMsec(total) << ' ' << this);
}