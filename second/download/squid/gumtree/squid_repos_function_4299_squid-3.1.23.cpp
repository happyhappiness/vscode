void
DestinationIPLookup::LookupDone(const ipcache_addrs *, const DnsLookupDetails &details, void *data)
{
    ACLFilledChecklist *checklist = Filled((ACLChecklist*)data);
    assert (checklist->asyncState() == DestinationIPLookup::Instance());
    checklist->request->flags.destinationIPLookupCompleted();
    checklist->request->recordLookup(details);
    checklist->asyncInProgress(false);
    checklist->changeState (ACLChecklist::NullState::Instance());
    checklist->check();
}