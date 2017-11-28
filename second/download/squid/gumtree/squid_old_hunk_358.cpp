           << " time=" << pastTime << ' ' << this);
}

void Adaptation::Icap::History::stop(const char *context)
{
    if (!concurrencyLevel) {
        debugs(93,1, HERE << "Internal error: poor history accounting " << this);
        return;
    }

    const int current = currentTime();
    debugs(93,4, HERE << "stop " << context << " level=" << concurrencyLevel <<
           " time=" << pastTime << '+' << current << ' ' << this);
