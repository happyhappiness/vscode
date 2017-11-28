bool Adaptation::Icap::Launcher::canRetry(Adaptation::Icap::XactAbortInfo &info) const
{
    // We do not check and can exceed zero repeat limit when retrying.
    // This is by design as the limit does not apply to pconn retrying.
    return !shutting_down && info.isRetriable;
}