void Adaptation::History::sumLogString(const char *serviceId, SBuf &s)
{
    s.clear();
    int retriedRptm = 0; // sum of rptm times of retried transactions
    for (auto & i : theEntries) {
        if (i.retried) { // do not log retried xact but accumulate their time
            retriedRptm += i.rptm();
        } else if (!serviceId || i.service == serviceId) {
            if (!s.isEmpty()) // not the first logged time, must delimit
                s.append(',');
            s.appendf("%d", retriedRptm + i.rptm());
            // continue; we may have two identical services (e.g., for retries)
        }

        if (!i.retried)
            retriedRptm = 0;
    }

    // the last transaction is never retried or it would not be the last
    Must(!retriedRptm);
}