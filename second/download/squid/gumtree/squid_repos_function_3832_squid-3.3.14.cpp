void Adaptation::History::allLogString(const char *serviceId, String &s)
{
    s="";
    bool prevWasRetried = false;
    // XXX: Fix Vector<> so that we can use const_iterator here
    typedef Adaptation::History::Entries::iterator ECI;
    for (ECI i = theEntries.begin(); i != theEntries.end(); ++i) {
        // TODO: here and below, optimize service ID comparison?
        if (!serviceId || i->service == serviceId) {
            if (s.size() > 0) // not the first logged time, must delimit
                s.append(prevWasRetried ? "+" : ",");

            char buf[64];
            snprintf(buf, sizeof(buf), "%d", i->rptm());
            s.append(buf);

            // continue; we may have two identical services (e.g., for retries)
        }
        prevWasRetried = i->retried;
    }
}