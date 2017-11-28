{
#if ICAP_CLIENT
    Adaptation::Icap::History::Pointer h = filter.request->icapHistory();
    if (h != NULL)
        h->stop("ACL");
#endif
    if (callback_data)
        cbdataReferenceDone(callback_data);
}

void
Adaptation::AccessCheck::start()
{
    AsyncJob::start();
    check();
}

/// Walk the access rules list to find rules with applicable service groups
void
Adaptation::AccessCheck::check()
{
