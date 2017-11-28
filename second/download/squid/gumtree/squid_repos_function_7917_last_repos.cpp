void
openlog(const char *ident, int logopt, int facility)
{
    if (ms_eventlog)
        return;

    ms_eventlog = RegisterEventSourceA(NULL, ident);

    // note: RegisterEventAtSourceA may fail and return NULL.
    //   in that case we'll just retry at the next message or not log
}