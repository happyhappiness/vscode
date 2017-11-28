void Adaptation::Icap::History::start(const char *context)
{
    if (!concurrencyLevel++)
        currentStart = current_time;

    debugs(93,4, HERE << "start " << context << " level=" << concurrencyLevel
           << " time=" << pastTime << ' ' << this);
}