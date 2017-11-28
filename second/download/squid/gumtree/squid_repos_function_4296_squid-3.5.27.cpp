int Adaptation::Icap::History::currentTime() const
{
    return concurrencyLevel > 0 ?
           max(0, tvSubMsec(currentStart, current_time)) : 0;
}