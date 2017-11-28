bool
AsyncCall::cancel(const char *reason)
{
    if (isCanceled)
        debugs(debugSection, debugLevel, HERE << "will not call " << name <<
               " [call"<< id << ']' << " also because " << reason);
    isCanceled = reason;
    return false;
}