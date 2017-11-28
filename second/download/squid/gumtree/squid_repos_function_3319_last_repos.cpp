void Adaptation::History::allLogString(const char *serviceId, SBuf &s)
{
    s.clear();
    bool prevWasRetried = false;
    for (auto &i : theEntries) {
        // TODO: here and below, optimize service ID comparison?
        if (!serviceId || i.service == serviceId) {
            if (!s.isEmpty()) // not the first logged time, must delimit
                s.append(prevWasRetried ? '+' : ',');
            s.appendf("%d", i.rptm());
            // continue; we may have two identical services (e.g., for retries)
        }
        prevWasRetried = i.retried;
    }
}