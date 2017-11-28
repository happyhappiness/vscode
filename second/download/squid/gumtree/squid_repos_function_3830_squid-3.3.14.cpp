int Adaptation::History::recordXactStart(const String &serviceId, const timeval &when, bool retrying)
{
    // the history will be empty on retries if it was enabled after the failure
    if (retrying && !theEntries.empty())
        theEntries.back().retried = true;

    theEntries.push_back(Adaptation::History::Entry(serviceId, when));
    return theEntries.size() - 1; // record position becomes history ID
}