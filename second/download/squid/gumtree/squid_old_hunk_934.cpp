void Adaptation::History::recordXactFinish(int hid)
{
    Must(0 <= hid && hid < static_cast<int>(theEntries.size()));
    theEntries[hid].stop();
}

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

void Adaptation::History::sumLogString(const char *serviceId, String &s)
{
    s="";
    int retriedRptm = 0; // sum of rptm times of retried transactions
    typedef Adaptation::History::Entries::iterator ECI;
    for (ECI i = theEntries.begin(); i != theEntries.end(); ++i) {
        if (i->retried) { // do not log retried xact but accumulate their time
            retriedRptm += i->rptm();
        } else if (!serviceId || i->service == serviceId) {
            if (s.size() > 0) // not the first logged time, must delimit
                s.append(",");

            char buf[64];
            snprintf(buf, sizeof(buf), "%d", retriedRptm + i->rptm());
            s.append(buf);

            // continue; we may have two identical services (e.g., for retries)
        }

        if (!i->retried)
            retriedRptm = 0;
    }

    // the last transaction is never retried or it would not be the last
    Must(!retriedRptm);
}
