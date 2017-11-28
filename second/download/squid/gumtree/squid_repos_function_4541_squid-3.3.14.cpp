void
DestinationIPLookup::LookupDone(const ipcache_addrs *, const DnsLookupDetails &details, void *data)
{
    ACLFilledChecklist *checklist = Filled((ACLChecklist*)data);
    assert (checklist->asyncState() == DestinationIPLookup::Instance());
    checklist->request->flags.destinationIpLookedUp=true;
    checklist->request->recordLookup(details);
    checklist->asyncInProgress(false);
    checklist->changeState (ACLChecklist::NullState::Instance());
    checklist->matchNonBlocking();
}