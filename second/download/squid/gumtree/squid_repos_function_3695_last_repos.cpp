void Adaptation::Icap::History::stop(const char *context)
{
    if (!concurrencyLevel) {
        debugs(93, DBG_IMPORTANT, HERE << "Internal error: poor history accounting " << this);
        return;
    }

    struct timeval current;
    currentTime(current);
    debugs(93,4, HERE << "stop " << context << " level=" << concurrencyLevel <<
           " time=" << tvToMsec(pastTime) << '+' << tvToMsec(current) << ' ' << this);

    if (!--concurrencyLevel)
        tvAssignAdd(pastTime, current);
}