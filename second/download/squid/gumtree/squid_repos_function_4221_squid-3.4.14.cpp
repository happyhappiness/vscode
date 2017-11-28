int Adaptation::Icap::History::processingTime() const
{
    const int total = pastTime + currentTime();
    debugs(93,7, HERE << " current total: " << total << ' ' << this);
    return total;
}