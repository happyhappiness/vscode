bool
AsyncCall::cancel(const char *reason)
{
    debugs(debugSection, debugLevel, HERE << "will not call " << name <<
           " [" << id << "] " << (isCanceled ? "also " : "") <<
           "because " << reason);

    isCanceled = reason;
    return false;
}