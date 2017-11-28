void Adaptation::History::Entry::stop()
{
    // theRptm may already be set if the access log entry has already been made
    (void)rptm(); // will cache result in theRptm if not set already
}